/*
 * eglstrm_common.h
 *
 * Copyright 2016 NVIDIA Corporation.  All rights reserved.
 *
 * Please refer to the NVIDIA end user license agreement (EULA) associated
 * with this source code for terms and conditions that govern your use of
 * this software. Any use, reproduction, disclosure, or distribution of
 * this software and related documentation outside the terms of the EULA
 * is strictly prohibited.
 *
 */


//
// DESCRIPTION:   Common EGL stream functions header file
//

#ifndef _EGLSTRM_COMMON_H_
#define _EGLSTRM_COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <signal.h>
#include <stdbool.h>

#include "helper_cuda_drvapi.h"
#include "cudaEGL.h"

#define EXTENSION_LIST(T) \
    T( PFNEGLCREATESTREAMKHRPROC,          eglCreateStreamKHR ) \
    T( PFNEGLDESTROYSTREAMKHRPROC,         eglDestroyStreamKHR ) \
    T( PFNEGLQUERYSTREAMKHRPROC,           eglQueryStreamKHR ) \
    T( PFNEGLQUERYSTREAMU64KHRPROC,        eglQueryStreamu64KHR ) \
    T( PFNEGLQUERYSTREAMTIMEKHRPROC,       eglQueryStreamTimeKHR ) \
    T( PFNEGLSTREAMATTRIBKHRPROC,          eglStreamAttribKHR ) \
    T( PFNEGLSTREAMCONSUMERACQUIREKHRPROC, eglStreamConsumerAcquireKHR ) \
    T( PFNEGLSTREAMCONSUMERRELEASEKHRPROC, eglStreamConsumerReleaseKHR ) \
    T( PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALKHRPROC, \
                                    eglStreamConsumerGLTextureExternalKHR ) \
    T( PFNEGLGETSTREAMFILEDESCRIPTORKHRPROC, eglGetStreamFileDescriptorKHR) \
    T( PFNEGLCREATESTREAMFROMFILEDESCRIPTORKHRPROC, eglCreateStreamFromFileDescriptorKHR) \
    T( PFNEGLCREATESTREAMPRODUCERSURFACEKHRPROC, eglCreateStreamProducerSurfaceKHR)

// See bug 200161837 on my EGL pointer functions should renamed starting with my_
// not renaming egl pointer function to start with my_ causes 64 bit app to crash
#define eglCreateStreamKHR                                      my_eglCreateStreamKHR 
#define eglDestroyStreamKHR                                     my_eglDestroyStreamKHR 
#define eglQueryStreamKHR                                       my_eglQueryStreamKHR 
#define eglQueryStreamu64KHR                                    my_eglQueryStreamu64KHR 
#define eglQueryStreamTimeKHR                                   my_eglQueryStreamTimeKHR 
#define eglStreamAttribKHR                                      my_eglStreamAttribKHR 
#define eglStreamConsumerAcquireKHR                             my_eglStreamConsumerAcquireKHR 
#define eglStreamConsumerReleaseKHR                             my_eglStreamConsumerReleaseKHR 
#define eglStreamConsumerGLTextureExternalKHR                   my_eglStreamConsumerGLTextureExternalKHR
#define eglGetStreamFileDescriptorKHR                           my_eglGetStreamFileDescriptorKHR
#define eglCreateStreamFromFileDescriptorKHR                    my_eglCreateStreamFromFileDescriptorKHR
#define eglCreateStreamProducerSurfaceKHR                       my_eglCreateStreamProducerSurfaceKHR

#define EXTLST_DECL(tx, x)  tx my_ ## x = NULL;
#define EXTLST_EXTERN(tx, x) extern tx my_ ## x;
#define EXTLST_ENTRY(tx, x) { (extlst_fnptr_t *)&my_ ## x, #x },

#define MAX_STRING_SIZE     256
#define WIDTH               1280
#define HEIGHT              720

typedef struct _TestArgs {
    char   *infile1;
    char   *infile2;
    bool   isARGB;
    unsigned int  inputWidth;
    unsigned int  inputHeight;
    bool pitchLinearOutput;
} TestArgs;


int eglSetupExtensions(void);
void PrintEGLStreamState(EGLint streamState);
int EGLStreamInit(void);
int EGLStreamCreateProducer(void);
void EGLStreamFini(void);
EGLBoolean eglQueryStreamKHR_wrapper(
    EGLDisplay   dpy,
    EGLStreamKHR stream,
    EGLenum      attribute,
    EGLint      *value);
void eglSwapBuffers_wrapper(void);
#endif
