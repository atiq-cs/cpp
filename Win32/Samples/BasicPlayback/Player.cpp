//////////////////////////////////////////////////////////////////////////
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
//////////////////////////////////////////////////////////////////////////

#include "BasicPlayback.h"
#include <assert.h>

HRESULT CreateSourceStreamNode(
    IMFMediaSource *pSource,
    IMFPresentationDescriptor *pSourcePD,
    IMFStreamDescriptor *pSourceSD,
    IMFTopologyNode **ppNode
    );

HRESULT CreateOutputNode(
    IMFStreamDescriptor *pSourceSD,
    HWND hwndVideo,
    IMFTopologyNode **ppNode
    );


//  Static class method to create the CPlayer object.
//
//  hVideo:   Handle to the video window.
//  hEvent:   Handle to the window to receive notifications.
//  ppPlayer: Receives an AddRef's pointer to the CPlayer object.
//            The caller must release the pointer.

HRESULT CPlayer::CreateInstance(HWND hVideo, HWND hEvent, CPlayer **ppPlayer)
{
    assert(hVideo != NULL);
    assert(hEvent != NULL);

    if (ppPlayer == NULL)
    {
        return E_POINTER;
    }

    HRESULT hr = S_OK;

    CPlayer *pPlayer = new CPlayer(hVideo, hEvent);

    if (pPlayer == NULL)
    {
        return E_OUTOFMEMORY;
    }

    hr = pPlayer->Initialize();

    if (SUCCEEDED(hr))
    {
        *ppPlayer = pPlayer;
        (*ppPlayer)->AddRef();
    }

    // The CPlayer constructor sets the ref count to 1.
    // If the method succeeds, the caller receives an AddRef'd pointer.
    // Whether the method succeeds or fails, we must release the pointer.

    SafeRelease(&pPlayer);

    return hr;
}


CPlayer::CPlayer(HWND hVideo, HWND hEvent) :
    m_pSession(NULL),
    m_pSource(NULL),
    m_pVideoDisplay(NULL),
    m_hwndVideo(hVideo),
    m_hwndEvent(hEvent),
    m_state(Closed),
    m_hCloseEvent(NULL),
    m_nRefCount(1)
{

}

CPlayer::~CPlayer()
{
    assert(m_pSession == NULL);  // If FALSE, the app did not call Shutdown().

    // The application must call Shutdown because the media session holds a 
    // reference count on the CPlayer object. (This happens when CPlayer calls 
    // IMediaEventGenerator::BeginGetEvent on the media session.) As a result,
    // there is a circular reference count between the CPlayer object and the 
    // media session. Calling Shutdown breaks the circular reference count.

    // If CreateInstance failed, the application will not call Shutdown. To 
    // handle that case, we must call Shutdown() in the destructor. The 
    // circular ref-count problem does not occcur if CreateInstance has failed. 
    // Also, calling Shutdown twice is harmless.

    Shutdown();
}



//  Initializes the CPlayer object. 

HRESULT CPlayer::Initialize()
{
    if (m_hCloseEvent)
    {
        return MF_E_ALREADY_INITIALIZED;
    }

    // Start up Media Foundation platform.
    HRESULT hr = MFStartup(MF_VERSION);
    if (FAILED(hr))
    {
        return hr;
    }

    m_hCloseEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (m_hCloseEvent == NULL)
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
    }
    return hr;
}

// IUnknown methods

HRESULT CPlayer::QueryInterface(REFIID riid, void** ppv)
{
    static const QITAB qit[] =
    {
        QITABENT(CPlayer, IMFAsyncCallback),
        { 0 },
    };
    return QISearch(this, qit, riid, ppv);
}

ULONG CPlayer::AddRef()
{
    return InterlockedIncrement(&m_nRefCount);
}

ULONG CPlayer::Release()
{
    ULONG uCount = InterlockedDecrement(&m_nRefCount);
    if (uCount == 0)
    {
        delete this;
    }
    return uCount;
}


// Opens a URL for playback.

HRESULT CPlayer::OpenURL(PCWSTR sURL)
{
    // 1. Create a new media session.
    // 2. Create the media source.
    // 3. Create the topology.
    // 4. Queue the topology [asynchronous]
    // 5. Start playback [asynchronous - does not happen in this method.]

    IMFTopology *pTopology = NULL;

    // Create the media session.
    HRESULT hr = CreateSession();
    if (FAILED(hr))
    {
        goto done;
    }

    // Create the media source.
    hr = CreateMediaSource(sURL);
    if (FAILED(hr))
    {
        goto done;
    }

    // Create a partial topology.
    hr = CreateTopologyFromSource(&pTopology);
    if (FAILED(hr))
    {
        goto done;
    }

    // Set the topology on the media session.
    hr = m_pSession->SetTopology(0, pTopology);
    if (FAILED(hr))
    {
        goto done;
    }

    // Set our state to "open pending"
    m_state = OpenPending;

    // If SetTopology succeeds, the media session will queue an
    // MESessionTopologySet event.

done:
    if (FAILED(hr))
    {
        m_state = Closed;
    }
    SafeRelease(&pTopology);
    return hr;
}


//  Starts playback from paused or stopped state.

HRESULT CPlayer::Play()
{
    if (m_state != Paused && m_state != Stopped)
    {
        return MF_E_INVALIDREQUEST;
    }
    if (m_pSession == NULL || m_pSource == NULL)
    {
        return E_UNEXPECTED;
    }

    HRESULT hr = StartPlayback();

    return hr;
}


//  Pauses playback.

HRESULT CPlayer::Pause()
{
    if (m_state != Started)
    {
        return MF_E_INVALIDREQUEST;
    }
    if (m_pSession == NULL || m_pSource == NULL)
    {
        return E_UNEXPECTED;
    }

    HRESULT hr = m_pSession->Pause();

    if (SUCCEEDED(hr))
    {
        m_state = Paused;
    }

    return hr;
}

//  Repaints the video window.
//
//  The application calls this method when it receives a WM_PAINT message.

HRESULT CPlayer::Repaint()
{
    HRESULT hr = S_OK;

    if (m_pVideoDisplay)
    {
        hr = m_pVideoDisplay->RepaintVideo();
    }
    return hr;
}


//  Resizes the video rectangle.
//
//  The application calls this method if the size of the video window changes; 
//  e.g., when the application receives a WM_SIZE message.

HRESULT CPlayer::ResizeVideo(WORD width, WORD height)
{
    HRESULT hr = S_OK;

    if (m_pVideoDisplay)
    {
        // Set the destination rectangle.
        // Leave the default source rectangle (0,0,1,1).

        RECT rcDest = { 0, 0, width, height };

        hr = m_pVideoDisplay->SetVideoPosition(NULL, &rcDest);
    }
    return hr;
}


//  Callback for asynchronous BeginGetEvent method.
//
//  pAsyncResult: Pointer to the result.

HRESULT CPlayer::Invoke(IMFAsyncResult *pResult)
{
    IMFMediaEvent *pEvent = NULL;

    // Get the event from the event queue.
    HRESULT hr = m_pSession->EndGetEvent(pResult, &pEvent);
    if (FAILED(hr))
    {
        goto done;
    }

    // Get the event type.
    MediaEventType meType;
    hr = pEvent->GetType(&meType);
    if (FAILED(hr))
    {
        goto done;
    }

    if (meType == MESessionClosed)
    {
        // If the session is closed, the application is waiting on the event 
        // handle. Also, do not request any more events from the session.

        SetEvent(m_hCloseEvent);
    }
    else
    {
        // For all other events, ask the media session for the
        // next event in the queue.
        hr = m_pSession->BeginGetEvent(this, NULL);
        if (FAILED(hr))
        {
            goto done;
        }
    }

    // For most events, post the event as a private window message to the
    // application. This lets the application process the event on its main 
    // thread.

    // However, if a call to IMFMediaSession::Close is pending, it means the
    // application is waiting on the m_hCloseEvent event handle. (Blocking
    // call.) In that case, we simply discard the event.

    // When IMFMediaSession::Close is called, MESessionClosed is NOT
    // necessarily the next event that we will receive. We may receive any 
    // number of other events before receiving MESessionClosed.

    if (m_state != Closing)
    {
        // Leave a reference count on the event.
        pEvent->AddRef();
        PostMessage(m_hwndEvent, WM_APP_PLAYER_EVENT, (WPARAM)pEvent, (LPARAM)0);
    }

done:
    SafeRelease(&pEvent);
    return S_OK;
}


//  Called by the application when it receives a WM_APP_PLAYER_EVENT
//  message.
//
//  This method is used to process media session events on the
//  application's main thread.
//
//  pUnkPtr: Pointer to the IUnknown interface of a media session
//  event (IMFMediaEvent).

HRESULT CPlayer::HandleEvent(UINT_PTR pUnkPtr)
{
    HRESULT hrStatus = S_OK;            // Event status
    MF_TOPOSTATUS TopoStatus = MF_TOPOSTATUS_INVALID; 

    IUnknown *pUnk = NULL;
    IMFMediaEvent *pEvent = NULL;

    // pUnkPtr is really an IUnknown pointer.
    pUnk = (IUnknown*)pUnkPtr;

    if (pUnk == NULL)
    {
        return E_POINTER;
    }

    HRESULT hr = pUnk->QueryInterface(IID_PPV_ARGS(&pEvent));
    if (FAILED(hr))
    {
        goto done;
    }

    // Get the event type.
    MediaEventType meType;
    hr = pEvent->GetType(&meType);
    if (FAILED(hr))
    {
        goto done;
    }

    // Get the event status. If the operation that triggered the event did
    // not succeed, the status is a failure code.
    hr = pEvent->GetStatus(&hrStatus);
    if (FAILED(hr))
    {
        goto done;
    }

    // Check if the async operation succeeded.
    if (FAILED(hrStatus))
    {
        hr = hrStatus;
        goto done;
    }

    // Switch on the event type. Update the internal state of the CPlayer as needed.
    switch(meType)
    {
    case MESessionTopologyStatus:
        // Get the status code.
        hr = pEvent->GetUINT32(MF_EVENT_TOPOLOGY_STATUS, (UINT32*)&TopoStatus);
        if (FAILED(hr))
        {
            goto done;
        }

        switch (TopoStatus)
        {
        case MF_TOPOSTATUS_READY:
            hr = OnTopologyReady(pEvent);
            break;
        default:
            // Nothing to do.
            break;
        }
        break;

    case MEEndOfPresentation:
        hr = OnPresentationEnded(pEvent);
        break;
    }

done:
    SafeRelease(&pUnk);
    SafeRelease(&pEvent);
    return hr;
}


//  Releases all resources held by this object.

HRESULT CPlayer::Shutdown()
{
    HRESULT hr = S_OK;

    // Close the session
    hr = CloseSession();

    // Shutdown the Media Foundation platform
    MFShutdown();

    if (m_hCloseEvent)
    {
        CloseHandle(m_hCloseEvent);
        m_hCloseEvent = NULL;
    }

    return hr;
}


///
/// All methods that follow are private to the CPlayer class.
///


//  Handler for MESessionTopologyReady event.
//
//  - The MESessionTopologySet event means the session queued the
//    topology, but the topology is not ready yet. Generally, the
//    application does not need to respond to this event, unless
//    there is an error.
//  - The MESessionTopologyReady event means the new topology is
//    ready for playback. After this event is received, any calls to
//    IMFGetService will get service interfaces from the new topology.
//-------------------------------------------------------------------

HRESULT CPlayer::OnTopologyReady(IMFMediaEvent *pEvent)
{
    SafeRelease(&m_pVideoDisplay);

    // Ask for the IMFVideoDisplayControl interface. This interface is 
    // implemented by the EVR and is exposed by the media session as a service.

    // Note: This call is expected to fail if the source does not have video.

    MFGetService(m_pSession, MR_VIDEO_RENDER_SERVICE, 
        IID_PPV_ARGS(&m_pVideoDisplay));

    HRESULT hr = StartPlayback();

    return hr;
}


//  Handler for MEEndOfPresentation event.

HRESULT CPlayer::OnPresentationEnded(IMFMediaEvent *pEvent)
{
    // The session puts itself into the stopped state automatically.
    m_state = Stopped;
    return S_OK;
}


//  Creates a new instance of the media session.

HRESULT CPlayer::CreateSession()
{
    // Close the old session, if any.
    HRESULT hr = CloseSession();
    if (FAILED(hr))
    {
        goto done;
    }

    assert(m_state == Closed);

    // Create the media session.
    hr = MFCreateMediaSession(NULL, &m_pSession);
    if (FAILED(hr))
    {
        goto done;
    }

    m_state = Ready;

    // Start pulling events from the media session
    hr = m_pSession->BeginGetEvent((IMFAsyncCallback*)this, NULL);
    if (FAILED(hr))
    {
        goto done;
    }

done:
    return hr;
}


//  Closes the media session.
//
//  The IMFMediaSession::Close method is asynchronous, but the CloseSession 
//  method waits on the MESessionClosed event. The MESessionClosed event is 
//  guaranteed to be the last event that the media session fires.

HRESULT CPlayer::CloseSession()
{
    HRESULT hr = S_OK;

    SafeRelease(&m_pVideoDisplay);

    // First close the media session.
    if (m_pSession)
    {
        DWORD dwWaitResult = 0;

        m_state = Closing;

        hr = m_pSession->Close();
        if (FAILED(hr))
        {
            goto done;
        }

        // Wait for the close operation to complete

        WaitForSingleObject(m_hCloseEvent, 5000);
        // Now there will be no more events from this session.
    }

    // Complete shutdown operations.

    // Shut down the media source. (Synchronous operation, no events.)
    if (m_pSource)
    {
        m_pSource->Shutdown();
    }

    // Shut down the media session. (Synchronous operation, no events.)
    if (m_pSession)
    {
        m_pSession->Shutdown();
    }

    SafeRelease(&m_pSource);
    SafeRelease(&m_pSession);

    m_state = Closed;

done:
    return hr;
}


//  Starts playback from the current position.

HRESULT CPlayer::StartPlayback()
{
    assert(m_pSession != NULL);

    PROPVARIANT varStart;
    PropVariantInit(&varStart);

    varStart.vt = VT_EMPTY;

    HRESULT hr = m_pSession->Start(&GUID_NULL, &varStart);
    if (SUCCEEDED(hr))
    {
        // Start is an asynchronous operation. However, we can treat our state 
        // as being already started. If Start fails later, we'll get an 
        // MESessionStarted event with an error code, and will update our state.
        m_state = Started;
    }

    PropVariantClear(&varStart);
    return hr;
}


//  Creates a media source from a URL.

HRESULT CPlayer::CreateMediaSource(PCWSTR sURL)
{
    MF_OBJECT_TYPE ObjectType = MF_OBJECT_INVALID;

    IMFSourceResolver* pSourceResolver = NULL;
    IUnknown* pSource = NULL;

    SafeRelease(&m_pSource);

    // Create the source resolver.
    HRESULT hr = MFCreateSourceResolver(&pSourceResolver);
    if (FAILED(hr))
    {
        goto done;
    }

    // Use the source resolver to create the media source.

    // Note: For simplicity this sample uses the synchronous method on
    // IMFSourceResolver to create the media source. However, creating a media 
    // source can take a noticeable amount of time, especially for a network 
    // source. For a more responsive UI, use the asynchronous 
    // BeginCreateObjectFromURL method.

    hr = pSourceResolver->CreateObjectFromURL(
                sURL,                       // URL of the source.
                MF_RESOLUTION_MEDIASOURCE,  // Create a source object.
                NULL,                       // Optional property store.
                &ObjectType,                // Receives the created object type.
                &pSource                    // Receives a pointer to the media source.
            );
    if (FAILED(hr))
    {
        goto done;
    }

    // Get the IMFMediaSource interface from the media source.
    hr = pSource->QueryInterface(IID_PPV_ARGS(&m_pSource));

done:
    SafeRelease(&pSourceResolver);
    SafeRelease(&pSource);
    return hr;
}



//  Creates a playback topology from the media source.
//
//  Pre-condition: The media source must be created already.
//                 Call CreateMediaSource() before calling this method.

HRESULT CPlayer::CreateTopologyFromSource(IMFTopology **ppTopology)
{
    assert(m_pSession != NULL);
    assert(m_pSource != NULL);

    IMFTopology *pTopology = NULL;
    IMFPresentationDescriptor* pSourcePD = NULL;
    DWORD cSourceStreams = 0;

    // Create a new topology.
    HRESULT hr = MFCreateTopology(&pTopology);
    if (FAILED(hr))
    {
        goto done;
    }

    // Create the presentation descriptor for the media source.
    hr = m_pSource->CreatePresentationDescriptor(&pSourcePD);
    if (FAILED(hr))
    {
        goto done;
    }

    // Get the number of streams in the media source.
    hr = pSourcePD->GetStreamDescriptorCount(&cSourceStreams);
    if (FAILED(hr))
    {
        goto done;
    }

    // For each stream, create the topology nodes and add them to the topology.
    for (DWORD i = 0; i < cSourceStreams; i++)
    {
        hr = AddBranchToPartialTopology(pTopology, pSourcePD, i);
        if (FAILED(hr))
        {
            goto done;
        }
    }

    // Return the IMFTopology pointer to the caller.
    *ppTopology = pTopology;
    (*ppTopology)->AddRef();

done:
    SafeRelease(&pTopology);
    SafeRelease(&pSourcePD);
    return hr;
}


//  Adds a topology branch for one stream.
//
//  pTopology: Pointer to the topology object.
//  pSourcePD: The source's presentation descriptor.
//  iStream: Index of the stream to render.
//
//  Pre-conditions: The topology must be created already.
//
//  Notes: For each stream, we must do the following:
//    1. Create a source node associated with the stream.
//    2. Create an output node for the renderer.
//    3. Connect the two nodes.
//  The media session will resolve the topology, so we do not have
//  to worry about decoders or other transforms.

HRESULT CPlayer::AddBranchToPartialTopology(
    IMFTopology *pTopology,
    IMFPresentationDescriptor *pSourcePD,
    DWORD iStream
    )
{
    assert(pTopology != NULL);

    IMFStreamDescriptor* pSourceSD = NULL;
    IMFTopologyNode* pSourceNode = NULL;
    IMFTopologyNode* pOutputNode = NULL;
    BOOL fSelected = FALSE;

    // Get the stream descriptor for this stream.
    HRESULT hr = pSourcePD->GetStreamDescriptorByIndex(iStream, &fSelected, &pSourceSD);
    if (FAILED(hr))
    {
        goto done;
    }

    // Create the topology branch only if the stream is selected.
    // Otherwise, do nothing.
    if (fSelected)
    {
        // Create a source node for this stream.
        hr = CreateSourceStreamNode(m_pSource, pSourcePD, pSourceSD, &pSourceNode);
        if (FAILED(hr))
        {
            goto done;
        }

        // Create the output node for the renderer.
        hr = CreateOutputNode(pSourceSD, m_hwndVideo, &pOutputNode);
        if (FAILED(hr))
        {
            goto done;
        }

        // Add both nodes to the topology.
        hr = pTopology->AddNode(pSourceNode);
        if (FAILED(hr))
        {
            goto done;
        }

        hr = pTopology->AddNode(pOutputNode);
        if (FAILED(hr))
        {
            goto done;
        }

        // Connect the source node to the output node.
        hr = pSourceNode->ConnectOutput(0, pOutputNode, 0);
    }

done:
    // Clean up.
    SafeRelease(&pSourceSD);
    SafeRelease(&pSourceNode);
    SafeRelease(&pOutputNode);
    return hr;
}



//  Creates a source-stream node for a stream.
//
//  pSource: Pointer to the media source that contains the stream.
//  pSourcePD: Presentation descriptor for the media source.
//  pSourceSD: Stream descriptor for the stream.
//  ppNode: Receives a pointer to the new node.

HRESULT CreateSourceStreamNode(
    IMFMediaSource *pSource,
    IMFPresentationDescriptor *pSourcePD,
    IMFStreamDescriptor *pSourceSD,
    IMFTopologyNode **ppNode
    )
{
    if (!pSource || !pSourcePD || !pSourceSD || !ppNode)
    {
        return E_POINTER;
    }

    IMFTopologyNode *pNode = NULL;

    // Create the source-stream node.
    HRESULT hr = MFCreateTopologyNode(MF_TOPOLOGY_SOURCESTREAM_NODE, &pNode);
    if (FAILED(hr))
    {
        goto done;
    }

    // Set attribute: Pointer to the media source.
    hr = pNode->SetUnknown(MF_TOPONODE_SOURCE, pSource);
    if (FAILED(hr))
    {
        goto done;
    }

    // Set attribute: Pointer to the presentation descriptor.
    hr = pNode->SetUnknown(MF_TOPONODE_PRESENTATION_DESCRIPTOR, pSourcePD);
    if (FAILED(hr))
    {
        goto done;
    }

    // Set attribute: Pointer to the stream descriptor.
    hr = pNode->SetUnknown(MF_TOPONODE_STREAM_DESCRIPTOR, pSourceSD);
    if (FAILED(hr))
    {
        goto done;
    }

    // Return the IMFTopologyNode pointer to the caller.
    *ppNode = pNode;
    (*ppNode)->AddRef();

done:
    SafeRelease(&pNode);
    return hr;
}




//  Creates an output node for a stream.
//
//  pSourceSD: Stream descriptor for the stream.
//  ppNode: Receives a pointer to the new node.
//
//  Notes:
//  This function does the following:
//  1. Chooses a renderer based on the media type of the stream.
//  2. Creates an IActivate object for the renderer.
//  3. Creates an output topology node.
//  4. Sets the IActivate pointer on the node.

HRESULT CreateOutputNode(
    IMFStreamDescriptor *pSourceSD,
    HWND hwndVideo,
    IMFTopologyNode **ppNode
    )
{

    IMFTopologyNode *pNode = NULL;
    IMFMediaTypeHandler *pHandler = NULL;
    IMFActivate *pRendererActivate = NULL;

    GUID guidMajorType = GUID_NULL;

    // Get the stream ID.
    DWORD streamID = 0;
    pSourceSD->GetStreamIdentifier(&streamID); // Just for debugging, ignore any failures.

    // Get the media type handler for the stream.
    HRESULT hr = pSourceSD->GetMediaTypeHandler(&pHandler);
    if (FAILED(hr))
    {
        goto done;
    }

    // Get the major media type.
    hr = pHandler->GetMajorType(&guidMajorType);
    if (FAILED(hr))
    {
        goto done;
    }

    // Create a downstream node.
    hr = MFCreateTopologyNode(MF_TOPOLOGY_OUTPUT_NODE, &pNode);
    if (FAILED(hr))
    {
        goto done;
    }

    // Create an IMFActivate object for the renderer, based on the media type.
    if (MFMediaType_Audio == guidMajorType)
    {
        // Create the audio renderer.
        hr = MFCreateAudioRendererActivate(&pRendererActivate);
    }
    else if (MFMediaType_Video == guidMajorType)
    {
        // Create the video renderer.
        hr = MFCreateVideoRendererActivate(hwndVideo, &pRendererActivate);
    }
    else
    {
        hr = E_FAIL;
    }
    if (FAILED(hr))
    {
        goto done;
    }

    // Set the IActivate object on the output node.
    hr = pNode->SetObject(pRendererActivate);
    if (FAILED(hr))
    {
        goto done;
    }

    // Return the IMFTopologyNode pointer to the caller.
    *ppNode = pNode;
    (*ppNode)->AddRef();

done:
    SafeRelease(&pNode);
    SafeRelease(&pHandler);
    SafeRelease(&pRendererActivate);
    return hr;
}
