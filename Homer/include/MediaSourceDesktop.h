/*****************************************************************************
 *
 * Copyright (C) 2008-2011 Homer-conferencing project
 *
 * This software is free software.
 * Your are allowed to redistribute it and/or modify it under the terms of
 * the GNU General Public License version 2 as published by the Free Software
 * Foundation.
 *
 * This source is published in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License version 2
 * along with this program. Otherwise, you can write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02111, USA.
 * Alternatively, you find an online version of the license text under
 * http://www.gnu.org/licenses/gpl-2.0.html.
 *
 *****************************************************************************/

/*
 * Purpose: desktop video source
 * Author:  Thomas Volkert
 * Since:   2010-02-15
 */

#ifndef _MEDIA_SOURCE_DESKTOP_
#define _MEDIA_SOURCE_DESKTOP_

#include <MediaSource.h>

#include <QWidget>
#include <QTime>
#include <QMutex>
#include <QWaitCondition>

namespace Homer { namespace Gui {

using namespace Homer::Multimedia;

///////////////////////////////////////////////////////////////////////////////

// the following de/activates debugging of packets
//#define MSD_DEBUG_PACKETS

#define MSD_BYTES_PER_PIXEL                         4 //RGBX
#define MIN_GRABBING_FPS							5

///////////////////////////////////////////////////////////////////////////////

class MediaSourceDesktop:
    public MediaSource
{
public:
    MediaSourceDesktop(std::string pDesiredDevice = "");

    virtual ~MediaSourceDesktop();

    /* video grabbing control */
    virtual GrabResolutions GetSupportedVideoGrabResolutions();
    virtual void StopGrabbing();
    virtual std::string GetCodecName();
    virtual std::string GetCodecLongName();
    void SelectSegment(QWidget *pParent = NULL);

    /* device control */
    virtual void getVideoDevices(VideoDevicesList &pVList);

    /* create screenshot and updates internal buffer */
    void CreateScreenshot();

public:
    virtual bool OpenVideoGrabDevice(int pResX = 352, int pResY = 288, float pFps = 29.97);
    virtual bool OpenAudioGrabDevice(int pSampleRate = 44100, bool pStereo = true);
    virtual bool CloseGrabDevice();
    virtual int GrabChunk(void* pChunkBuffer, int& pChunkSize, bool pDropChunk = false);

protected:
    /* internal video resolution switch */
    virtual void DoSetVideoGrabResolution(int pResX = 352, int pResY = 288);

private:
    friend class SegmentSelectionDialog;

    QPainter            *mTargetPainter;
    QWidget             *mWidget;
    int                 mGrabOffsetX, mGrabOffsetY;
    void                *mScreenshot;
    bool                mScreenshotUpdated;
    QTime               mLastTimeGrabbed;
    QMutex				mMutexScreenshot, mMutexGrabberActive;
    QWaitCondition      mWaitConditionScreenshotUpdated;
};

///////////////////////////////////////////////////////////////////////////////

}} // namespace

#endif