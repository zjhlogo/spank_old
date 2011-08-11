//
//  OpenGLView.m
//  HelloOpenGL
//
//  Created by Ray Wenderlich on 5/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "OpenGLView.h"
#import <GLES2/gl2.h>
#import <GLES2/gl2ext.h>
#include <util/ConfigUtil.h>
#include <ICore.h>
#include <InputMgr.h>
#include <IRenderer2D.h>

@implementation OpenGLView

+ (Class)layerClass {
    return [CAEAGLLayer class];
}

- (void)setupLayer {
    _eaglLayer = (CAEAGLLayer*) self.layer;
    _eaglLayer.opaque = YES;
}

- (void)setupContext {   
    EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;
    _context = [[EAGLContext alloc] initWithAPI:api];
    if (!_context) {
        NSLog(@"Failed to initialize OpenGLES 2.0 context");
        exit(1);
    }
    
    if (![EAGLContext setCurrentContext:_context]) {
        NSLog(@"Failed to set current OpenGL context");
        exit(1);
    }
}

- (void)setupRenderBuffer {
    glGenRenderbuffers(1, &_colorRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _colorRenderBuffer);
    [_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:_eaglLayer];
}

- (void)setupDepthBuffer {
    glGenRenderbuffers(1, &_depthRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _depthRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, self.frame.size.width, self.frame.size.height);
}

- (void)setupFrameBuffer {
    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _colorRenderBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthRenderBuffer);
}

- (void)render:(CADisplayLink*)displayLink {
	ICore::GetInstance().Update(1.0f/60.0f);
	
	ICore::GetInstance().PreRender();
	ICore::GetInstance().Render();
	ICore::GetInstance().PostRender();
	
    [_context presentRenderbuffer:GL_RENDERBUFFER];
}

- (void)setupDisplayLink {
    CADisplayLink* displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(render:)];
    [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
}

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        [self setupLayer];
        [self setupContext];
        [self setupDepthBuffer];
        [self setupRenderBuffer];
        [self setupFrameBuffer];
		
		ConfigUtil::GetInstance().AddInt("SURFACE_WIDTH", self.frame.size.width);
		ConfigUtil::GetInstance().AddInt("SURFACE_HEIGHT", self.frame.size.height);
		ICore::GetInstance().Initialize();
		
		// setup the rotation matrix to rotate world as landscape
		Matrix4x4 matRot;
		IMath::BuildRotateMatrixZ(matRot, -3.14159f/2.0f);
		Matrix4x4 matProj = IRenderer2D::GetInstance().GetProjectionMatrix() * matRot;
		IRenderer2D::GetInstance().SetProjectionMatrix(matProj);
		
        [self setupDisplayLink];
    }
    return self;
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
	CGPoint pos = [[touches anyObject] locationInView: self.superview];
	InputMgr::GetInstance().OnTouchStart(0, pos.x, pos.y);
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
	CGPoint pos = [[touches anyObject] locationInView: self.superview];
	InputMgr::GetInstance().OnTouchMove(0, pos.x, pos.y);
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	CGPoint pos = [[touches anyObject] locationInView: self.superview];
	InputMgr::GetInstance().OnTouchEnd(0, pos.x, pos.y);
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
	CGPoint pos = [[touches anyObject] locationInView: self.superview];
	InputMgr::GetInstance().OnTouchEnd(0, pos.x, pos.y);
}

- (void)dealloc
{
	ICore::GetInstance().Terminate();
    [_context release];
    _context = nil;
    [super dealloc];
}

@end
