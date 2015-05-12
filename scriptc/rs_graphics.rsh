/*
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Don't edit this file!  It is auto-generated by frameworks/rs/api/generate.sh.

/*
 * rs_graphics.rsh: Graphics Functions and Types
 *
 * The graphics subsystem of RenderScript was removed at API level 23.
 */

#ifndef RENDERSCRIPT_RS_GRAPHICS_RSH
#define RENDERSCRIPT_RS_GRAPHICS_RSH

#ifdef __LP64__
// TODO We need to fix some of the builds before enabling this error:
// #error "RenderScript graphics is deprecated and not supported in 64bit mode."
#endif

// TODO we seem to assume order for the other headers too.
#include "rs_object_types.rsh"

/*
 * rs_blend_src_func: Blend source function
 *
 * DEPRECATED.  Do not use.
 *
 */
#ifndef __LP64__
#if (defined(RS_VERSION) && (RS_VERSION >= 16) && (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22))
typedef enum {
    RS_BLEND_SRC_ZERO = 0,
    RS_BLEND_SRC_ONE = 1,
    RS_BLEND_SRC_DST_COLOR = 2,
    RS_BLEND_SRC_ONE_MINUS_DST_COLOR = 3,
    RS_BLEND_SRC_SRC_ALPHA = 4,
    RS_BLEND_SRC_ONE_MINUS_SRC_ALPHA = 5,
    RS_BLEND_SRC_DST_ALPHA = 6,
    RS_BLEND_SRC_ONE_MINUS_DST_ALPHA = 7,
    RS_BLEND_SRC_SRC_ALPHA_SATURATE = 8,
    RS_BLEND_SRC_INVALID = 100
} rs_blend_src_func;
#endif
#endif

/*
 * rs_blend_dst_func: Blend destination function
 *
 * DEPRECATED.  Do not use.
 *
 */
#ifndef __LP64__
#if (defined(RS_VERSION) && (RS_VERSION >= 16) && (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22))
typedef enum {
    RS_BLEND_DST_ZERO = 0,
    RS_BLEND_DST_ONE = 1,
    RS_BLEND_DST_SRC_COLOR = 2,
    RS_BLEND_DST_ONE_MINUS_SRC_COLOR = 3,
    RS_BLEND_DST_SRC_ALPHA = 4,
    RS_BLEND_DST_ONE_MINUS_SRC_ALPHA = 5,
    RS_BLEND_DST_DST_ALPHA = 6,
    RS_BLEND_DST_ONE_MINUS_DST_ALPHA = 7,
    RS_BLEND_DST_INVALID = 100
} rs_blend_dst_func;
#endif
#endif

/*
 * rs_cull_mode: Culling mode
 *
 * DEPRECATED.  Do not use.
 *
 */
#ifndef __LP64__
#if (defined(RS_VERSION) && (RS_VERSION >= 16) && (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22))
typedef enum {
    RS_CULL_BACK = 0,
    RS_CULL_FRONT = 1,
    RS_CULL_NONE = 2,
    RS_CULL_INVALID = 100
} rs_cull_mode;
#endif
#endif

/*
 * rs_depth_func: Depth function
 *
 * DEPRECATED.  Do not use.
 *
 * Specifies conditional drawing depending on the comparison of the incoming
 * depth to that found in the depth buffer.
 */
#ifndef __LP64__
#if (defined(RS_VERSION) && (RS_VERSION >= 16) && (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22))
typedef enum {
    RS_DEPTH_FUNC_ALWAYS = 0, // Always drawn
    RS_DEPTH_FUNC_LESS = 1, // Drawn if the incoming depth value is less than that in the depth buffer
    RS_DEPTH_FUNC_LEQUAL = 2, // Drawn if the incoming depth value is less or equal to that in the depth buffer
    RS_DEPTH_FUNC_GREATER = 3, // Drawn if the incoming depth value is greater than that in the depth buffer
    RS_DEPTH_FUNC_GEQUAL = 4, // Drawn if the incoming depth value is greater or equal to that in the depth buffer
    RS_DEPTH_FUNC_EQUAL = 5, // Drawn if the incoming depth value is equal to that in the depth buffer
    RS_DEPTH_FUNC_NOTEQUAL = 6, // Drawn if the incoming depth value is not equal to that in the depth buffer
    RS_DEPTH_FUNC_INVALID = 100 // Invalid depth function
} rs_depth_func;
#endif
#endif

/*
 * rs_primitive: How to intepret mesh vertex data
 *
 * DEPRECATED.  Do not use.
 *
 * Describes the way mesh vertex data is interpreted when rendering
 */
#ifndef __LP64__
#if (defined(RS_VERSION) && (RS_VERSION >= 16) && (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22))
typedef enum {
    RS_PRIMITIVE_POINT = 0, // Vertex data will be rendered as a series of points
    RS_PRIMITIVE_LINE = 1, // Vertex pairs will be rendered as lines
    RS_PRIMITIVE_LINE_STRIP = 2, // Vertex data will be rendered as a connected line strip
    RS_PRIMITIVE_TRIANGLE = 3, // Vertices will be rendered as individual triangles
    RS_PRIMITIVE_TRIANGLE_STRIP = 4, // Vertices will be rendered as a connected triangle strip defined by the first three vertices with each additional triangle defined by a new vertex
    RS_PRIMITIVE_TRIANGLE_FAN = 5, // Vertices will be rendered as a sequence of triangles that all share first vertex as the origin
    RS_PRIMITIVE_INVALID = 100 // Invalid primitive
} rs_primitive;
#endif
#endif

/*
 * rs_font: Handle to a Font
 *
 * DEPRECATED.  Do not use.
 *
 * Opaque handle to a RenderScript font object.
 * See: android.renderscript.Font
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
typedef _RS_HANDLE rs_font;
#endif
#endif

/*
 * rs_mesh: Handle to a Mesh
 *
 * DEPRECATED.  Do not use.
 *
 * Opaque handle to a RenderScript mesh object.
 * See: android.renderscript.Mesh
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
typedef _RS_HANDLE rs_mesh;
#endif
#endif

/*
 * rs_program_fragment: Handle to a ProgramFragment
 *
 * DEPRECATED.  Do not use.
 *
 * Opaque handle to a RenderScript ProgramFragment object.
 * See: android.renderscript.ProgramFragment
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
typedef _RS_HANDLE rs_program_fragment;
#endif
#endif

/*
 * rs_program_vertex: Handle to a ProgramVertex
 *
 * DEPRECATED.  Do not use.
 *
 * Opaque handle to a RenderScript ProgramVertex object.
 * See: android.renderscript.ProgramVertex
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
typedef _RS_HANDLE rs_program_vertex;
#endif
#endif

/*
 * rs_program_raster: Handle to a ProgramRaster
 *
 * DEPRECATED.  Do not use.
 *
 * Opaque handle to a RenderScript ProgramRaster object.
 * See: android.renderscript.ProgramRaster
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
typedef _RS_HANDLE rs_program_raster;
#endif
#endif

/*
 * rs_program_store: Handle to a ProgramStore
 *
 * DEPRECATED.  Do not use.
 *
 * Opaque handle to a RenderScript ProgramStore object.
 * See: android.renderscript.ProgramStore
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
typedef _RS_HANDLE rs_program_store;
#endif
#endif

/*
 * rsClearObject: Release an object
 *
 * Tells the run time that this handle will no longer be used to access the the related
 * object.  If this was the last handle to that object, resource recovery may happen.
 *
 * After calling this function, *dst will be set to an empty handle.  See rsIsObject().
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsClearObject(rs_mesh* dst);
#endif
#endif

#ifndef __LP64__
#if !defined(RS_VERSION) || (RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsClearObject(rs_program_fragment* dst);
#endif
#endif

#ifndef __LP64__
#if !defined(RS_VERSION) || (RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsClearObject(rs_program_vertex* dst);
#endif
#endif

#ifndef __LP64__
#if !defined(RS_VERSION) || (RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsClearObject(rs_program_raster* dst);
#endif
#endif

#ifndef __LP64__
#if !defined(RS_VERSION) || (RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsClearObject(rs_program_store* dst);
#endif
#endif

#ifndef __LP64__
#if !defined(RS_VERSION) || (RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsClearObject(rs_font* dst);
#endif
#endif

/*
 * rsIsObject: Check for an empty handle
 *
 * Returns true if the handle contains a non-null reference.
 *
 * This function does not validate that the internal pointer used in the handle
 * points to an actual valid object; it only checks for null.
 *
 * This function can be used to check the Element returned by rsElementGetSubElement()
 * or see if rsClearObject() has been called on a handle.
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (RS_VERSION <= 22)
extern bool __attribute__((overloadable))
    rsIsObject(rs_mesh v);
#endif
#endif

#ifndef __LP64__
#if !defined(RS_VERSION) || (RS_VERSION <= 22)
extern bool __attribute__((overloadable))
    rsIsObject(rs_program_fragment v);
#endif
#endif

#ifndef __LP64__
#if !defined(RS_VERSION) || (RS_VERSION <= 22)
extern bool __attribute__((overloadable))
    rsIsObject(rs_program_vertex v);
#endif
#endif

#ifndef __LP64__
#if !defined(RS_VERSION) || (RS_VERSION <= 22)
extern bool __attribute__((overloadable))
    rsIsObject(rs_program_raster v);
#endif
#endif

#ifndef __LP64__
#if !defined(RS_VERSION) || (RS_VERSION <= 22)
extern bool __attribute__((overloadable))
    rsIsObject(rs_program_store v);
#endif
#endif

#ifndef __LP64__
#if !defined(RS_VERSION) || (RS_VERSION <= 22)
extern bool __attribute__((overloadable))
    rsIsObject(rs_font v);
#endif
#endif

/*
 * rsSetObject: For internal use.
 *
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsSetObject(rs_mesh* dst, rs_mesh src);
#endif
#endif

#ifndef __LP64__
#if !defined(RS_VERSION) || (RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsSetObject(rs_program_fragment* dst, rs_program_fragment src);
#endif
#endif

#ifndef __LP64__
#if !defined(RS_VERSION) || (RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsSetObject(rs_program_vertex* dst, rs_program_vertex src);
#endif
#endif

#ifndef __LP64__
#if !defined(RS_VERSION) || (RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsSetObject(rs_program_raster* dst, rs_program_raster src);
#endif
#endif

#ifndef __LP64__
#if !defined(RS_VERSION) || (RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsSetObject(rs_program_store* dst, rs_program_store src);
#endif
#endif

#ifndef __LP64__
#if !defined(RS_VERSION) || (RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsSetObject(rs_font* dst, rs_font src);
#endif
#endif

/*
 * rsgAllocationSyncAll: Sync the contents of an allocation
 *
 * DEPRECATED.  Do not use.
 *
 * Sync the contents of an allocation.
 *
 * If the source is specified, sync from memory space specified by source.
 *
 * If the source is not specified, sync from its SCRIPT memory space to its HW
 * memory spaces.
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsgAllocationSyncAll(rs_allocation alloc);
#endif
#endif

#ifndef __LP64__
#if (defined(RS_VERSION) && (RS_VERSION >= 14) && (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22))
extern void __attribute__((overloadable))
    rsgAllocationSyncAll(rs_allocation alloc, rs_allocation_usage_type source);
#endif
#endif

/*
 * rsgBindColorTarget: Set the color target
 *
 * DEPRECATED.  Do not use.
 *
 * Set the color target used for all subsequent rendering calls
 */
#ifndef __LP64__
#if (defined(RS_VERSION) && (RS_VERSION >= 14) && (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22))
extern void __attribute__((overloadable))
    rsgBindColorTarget(rs_allocation colorTarget, uint slot);
#endif
#endif

/*
 * rsgBindConstant: Bind a constant allocation
 *
 * DEPRECATED.  Do not use.
 *
 * Bind a new Allocation object to a ProgramFragment or ProgramVertex.
 * The Allocation must be a valid constant input for the Program.
 *
 * Parameters:
 *   ps: program fragment object
 *   slot: index of the constant buffer on the program
 *   c: constants to bind
 *   pv: program vertex object
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsgBindConstant(rs_program_fragment ps, uint slot, rs_allocation c);
#endif
#endif

#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsgBindConstant(rs_program_vertex pv, uint slot, rs_allocation c);
#endif
#endif

/*
 * rsgBindDepthTarget: Set the depth target
 *
 * DEPRECATED.  Do not use.
 *
 * Set the depth target used for all subsequent rendering calls
 */
#ifndef __LP64__
#if (defined(RS_VERSION) && (RS_VERSION >= 14) && (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22))
extern void __attribute__((overloadable))
    rsgBindDepthTarget(rs_allocation depthTarget);
#endif
#endif

/*
 * rsgBindFont: Bind a font object
 *
 * DEPRECATED.  Do not use.
 *
 * Binds the font object to be used for all subsequent font rendering calls
 *
 * Parameters:
 *   font: object to bind
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsgBindFont(rs_font font);
#endif
#endif

/*
 * rsgBindProgramFragment: Bind a ProgramFragment
 *
 * DEPRECATED.  Do not use.
 *
 * Bind a new ProgramFragment to the rendering context.
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsgBindProgramFragment(rs_program_fragment pf);
#endif
#endif

/*
 * rsgBindProgramRaster: Bind a ProgramRaster
 *
 * DEPRECATED.  Do not use.
 *
 * Bind a new ProgramRaster to the rendering context.
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsgBindProgramRaster(rs_program_raster pr);
#endif
#endif

/*
 * rsgBindProgramStore: Bind a ProgramStore
 *
 * DEPRECATED.  Do not use.
 *
 * Bind a new ProgramStore to the rendering context.
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsgBindProgramStore(rs_program_store ps);
#endif
#endif

/*
 * rsgBindProgramVertex: Bind a ProgramVertex
 *
 * DEPRECATED.  Do not use.
 *
 * Bind a new ProgramVertex to the rendering context.
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsgBindProgramVertex(rs_program_vertex pv);
#endif
#endif

/*
 * rsgBindSampler: Bind a sampler
 *
 * DEPRECATED.  Do not use.
 *
 * Bind a new Sampler object to a ProgramFragment.  The sampler will
 * operate on the texture bound at the matching slot.
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsgBindSampler(rs_program_fragment fragment, uint slot, rs_sampler sampler);
#endif
#endif

/*
 * rsgBindTexture: Bind a texture allocation
 *
 * DEPRECATED.  Do not use.
 *
 * Bind a new Allocation object to a ProgramFragment.  The
 * Allocation must be a valid texture for the Program.  The sampling
 * of the texture will be controled by the Sampler bound at the
 * matching slot.
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsgBindTexture(rs_program_fragment v, uint slot, rs_allocation alloc);
#endif
#endif

/*
 * rsgClearAllRenderTargets: Clear all color and depth targets
 *
 * DEPRECATED.  Do not use.
 *
 * Clear all color and depth targets and resume rendering into
 * the framebuffer
 */
#ifndef __LP64__
#if (defined(RS_VERSION) && (RS_VERSION >= 14) && (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22))
extern void __attribute__((overloadable))
    rsgClearAllRenderTargets(void);
#endif
#endif

/*
 * rsgClearColor: Clear the specified color from the surface
 *
 * DEPRECATED.  Do not use.
 *
 * Clears the rendering surface to the specified color.
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsgClearColor(float r, float g, float b, float a);
#endif
#endif

/*
 * rsgClearColorTarget: Clear the color target
 *
 * DEPRECATED.  Do not use.
 *
 * Clear the previously set color target
 */
#ifndef __LP64__
#if (defined(RS_VERSION) && (RS_VERSION >= 14) && (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22))
extern void __attribute__((overloadable))
    rsgClearColorTarget(uint slot);
#endif
#endif

/*
 * rsgClearDepth: Clear the depth surface
 *
 * DEPRECATED.  Do not use.
 *
 * Clears the depth suface to the specified value.
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsgClearDepth(float value);
#endif
#endif

/*
 * rsgClearDepthTarget: Clear the depth target
 *
 * DEPRECATED.  Do not use.
 *
 * Clear the previously set depth target
 */
#ifndef __LP64__
#if (defined(RS_VERSION) && (RS_VERSION >= 14) && (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22))
extern void __attribute__((overloadable))
    rsgClearDepthTarget(void);
#endif
#endif

/*
 * rsgDrawMesh: Draw a mesh
 *
 * DEPRECATED.  Do not use.
 *
 * Draw a mesh using the current context state.
 *
 * If primitiveIndex is specified, draw part of a mesh using the current context state.
 *
 * If start and len are also specified, draw specified index range of part of a mesh using the current context state.
 *
 * Otherwise the whole mesh is rendered.
 *
 * Parameters:
 *   ism: mesh object to render
 *   primitiveIndex: for meshes that contain multiple primitive groups this parameter specifies the index of the group to draw.
 *   start: starting index in the range
 *   len: number of indices to draw
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsgDrawMesh(rs_mesh ism);
#endif
#endif

#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsgDrawMesh(rs_mesh ism, uint primitiveIndex);
#endif
#endif

#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsgDrawMesh(rs_mesh ism, uint primitiveIndex, uint start, uint len);
#endif
#endif

/*
 * rsgDrawQuad: Draw a quad
 *
 * DEPRECATED.  Do not use.
 *
 * Low performance utility function for drawing a simple quad.  Not intended for
 * drawing large quantities of geometry.
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsgDrawQuad(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3,
                float z3, float x4, float y4, float z4);
#endif
#endif

/*
 * rsgDrawQuadTexCoords: Draw a textured quad
 *
 * DEPRECATED.  Do not use.
 *
 * Low performance utility function for drawing a textured quad.  Not intended
 * for drawing large quantities of geometry.
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsgDrawQuadTexCoords(float x1, float y1, float z1, float u1, float v1, float x2, float y2,
                         float z2, float u2, float v2, float x3, float y3, float z3, float u3,
                         float v3, float x4, float y4, float z4, float u4, float v4);
#endif
#endif

/*
 * rsgDrawRect: Draw a rectangle
 *
 * DEPRECATED.  Do not use.
 *
 * Low performance utility function for drawing a simple rectangle.  Not
 * intended for drawing large quantities of geometry.
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsgDrawRect(float x1, float y1, float x2, float y2, float z);
#endif
#endif

/*
 * rsgDrawSpriteScreenspace: Draw rectangles in screenspace
 *
 * DEPRECATED.  Do not use.
 *
 * Low performance function for drawing rectangles in screenspace.  This
 * function uses the default passthough ProgramVertex.  Any bound ProgramVertex
 * is ignored.  This function has considerable overhead and should not be used
 * for drawing in shipping applications.
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsgDrawSpriteScreenspace(float x, float y, float z, float w, float h);
#endif
#endif

/*
 * rsgDrawText: Draw a text string
 *
 * DEPRECATED.  Do not use.
 *
 * Draws text given a string and location
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsgDrawText(const char* text, int x, int y);
#endif
#endif

#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsgDrawText(rs_allocation alloc, int x, int y);
#endif
#endif

/*
 * rsgFinish: End rendering commands
 *
 * DEPRECATED.  Do not use.
 *
 * Force RenderScript to finish all rendering commands
 */
#ifndef __LP64__
#if (defined(RS_VERSION) && (RS_VERSION >= 14) && (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22))
extern uint __attribute__((overloadable))
    rsgFinish(void);
#endif
#endif

/*
 * rsgFontColor: Set the font color
 *
 * DEPRECATED.  Do not use.
 *
 * Sets the font color for all subsequent rendering calls
 *
 * Parameters:
 *   r: red component
 *   g: green component
 *   b: blue component
 *   a: alpha component
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsgFontColor(float r, float g, float b, float a);
#endif
#endif

/*
 * rsgGetHeight: Get the surface height
 *
 * DEPRECATED.  Do not use.
 *
 * Get the height of the current rendering surface.
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
extern uint __attribute__((overloadable))
    rsgGetHeight(void);
#endif
#endif

/*
 * rsgGetWidth: Get the surface width
 *
 * DEPRECATED.  Do not use.
 *
 * Get the width of the current rendering surface.
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
extern uint __attribute__((overloadable))
    rsgGetWidth(void);
#endif
#endif

/*
 * rsgMeasureText: Get the bounding box for a text string
 *
 * DEPRECATED.  Do not use.
 *
 * Returns the bounding box of the text relative to (0, 0)
 * Any of left, right, top, bottom could be NULL
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsgMeasureText(const char* text, int* left, int* right, int* top, int* bottom);
#endif
#endif

#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsgMeasureText(rs_allocation alloc, int* left, int* right, int* top, int* bottom);
#endif
#endif

/*
 * rsgMeshComputeBoundingBox: Compute a bounding box
 *
 * DEPRECATED.  Do not use.
 *
 * Computes an axis aligned bounding box of a mesh object
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsgMeshComputeBoundingBox(rs_mesh mesh, float* minX, float* minY, float* min, float* maxX,
                              float* maxY, float* maxZ);
#endif
#endif

#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
static inline void __attribute__((always_inline, overloadable))
    rsgMeshComputeBoundingBox(rs_mesh mesh, float3* bBoxMin, float3* bBoxMax) {
    float x1, y1, z1, x2, y2, z2;
    rsgMeshComputeBoundingBox(mesh, &x1, &y1, &z1, &x2, &y2, &z2);
    bBoxMin->x = x1;
    bBoxMin->y = y1;
    bBoxMin->z = z1;
    bBoxMax->x = x2;
    bBoxMax->y = y2;
    bBoxMax->z = z2;
}
#endif
#endif

/*
 * rsgMeshGetIndexAllocation: Return an allocation containing index data
 *
 * DEPRECATED.  Do not use.
 *
 * Returns an allocation containing index data or a null
 * allocation if only the primitive is specified
 *
 * Parameters:
 *   m: mesh to get data from
 *   index: index of the index allocation
 *
 * Returns: allocation containing index data
 */
#ifndef __LP64__
#if (defined(RS_VERSION) && (RS_VERSION >= 16) && (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22))
extern rs_allocation __attribute__((overloadable))
    rsgMeshGetIndexAllocation(rs_mesh m, uint32_t index);
#endif
#endif

/*
 * rsgMeshGetPrimitive: Return the primitive
 *
 * DEPRECATED.  Do not use.
 *
 * Returns the primitive describing how a part of the mesh is
 * rendered
 *
 * Parameters:
 *   m: mesh to get data from
 *   index: index of the primitive
 *
 * Returns: primitive describing how the mesh is rendered
 */
#ifndef __LP64__
#if (defined(RS_VERSION) && (RS_VERSION >= 16) && (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22))
extern rs_primitive __attribute__((overloadable))
    rsgMeshGetPrimitive(rs_mesh m, uint32_t index);
#endif
#endif

/*
 * rsgMeshGetPrimitiveCount: Return the number of index sets
 *
 * DEPRECATED.  Do not use.
 *
 * Meshes could have multiple index sets, this function returns
 * the number.
 *
 * Parameters:
 *   m: mesh to get data from
 *
 * Returns: number of primitive groups in the mesh. This would include simple primitives as well as allocations containing index data
 */
#ifndef __LP64__
#if (defined(RS_VERSION) && (RS_VERSION >= 16) && (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22))
extern uint32_t __attribute__((overloadable))
    rsgMeshGetPrimitiveCount(rs_mesh m);
#endif
#endif

/*
 * rsgMeshGetVertexAllocation: Return a vertex allocation
 *
 * DEPRECATED.  Do not use.
 *
 * Returns an allocation that is part of the mesh and contains
 * vertex data, e.g. positions, normals, texcoords
 *
 * Parameters:
 *   m: mesh to get data from
 *   index: index of the vertex allocation
 *
 * Returns: allocation containing vertex data
 */
#ifndef __LP64__
#if (defined(RS_VERSION) && (RS_VERSION >= 16) && (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22))
extern rs_allocation __attribute__((overloadable))
    rsgMeshGetVertexAllocation(rs_mesh m, uint32_t index);
#endif
#endif

/*
 * rsgMeshGetVertexAllocationCount: Return the number of vertex allocations
 *
 * DEPRECATED.  Do not use.
 *
 * Returns the number of allocations in the mesh that contain
 * vertex data
 *
 * Parameters:
 *   m: mesh to get data from
 *
 * Returns: number of allocations in the mesh that contain vertex data
 */
#ifndef __LP64__
#if (defined(RS_VERSION) && (RS_VERSION >= 16) && (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22))
extern uint32_t __attribute__((overloadable))
    rsgMeshGetVertexAllocationCount(rs_mesh m);
#endif
#endif

/*
 * rsgProgramFragmentConstantColor: Set the constant color for a fixed function emulation program
 *
 * DEPRECATED.  Do not use.
 *
 * Set the constant color for a fixed function emulation program.
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsgProgramFragmentConstantColor(rs_program_fragment pf, float r, float g, float b, float a);
#endif
#endif

/*
 * rsgProgramVertexGetProjectionMatrix: Get the projection matrix for a fixed function vertex program
 *
 * DEPRECATED.  Do not use.
 *
 * Get the projection matrix for a currently bound fixed function
 * vertex program. Calling this function with a custom vertex shader
 * would result in an error.
 *
 * Parameters:
 *   proj: matrix to store the current projection matrix into
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsgProgramVertexGetProjectionMatrix(rs_matrix4x4* proj);
#endif
#endif

/*
 * rsgProgramVertexLoadModelMatrix: Load the model matrix for a bound fixed function vertex program
 *
 * DEPRECATED.  Do not use.
 *
 * Load the model matrix for a currently bound fixed function
 * vertex program. Calling this function with a custom vertex shader
 * would result in an error.
 *
 * Parameters:
 *   model: model matrix
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsgProgramVertexLoadModelMatrix(const rs_matrix4x4* model);
#endif
#endif

/*
 * rsgProgramVertexLoadProjectionMatrix: Load the projection matrix for a bound fixed function vertex program
 *
 * DEPRECATED.  Do not use.
 *
 * Load the projection matrix for a currently bound fixed function
 * vertex program. Calling this function with a custom vertex shader
 * would result in an error.
 *
 * Parameters:
 *   proj: projection matrix
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsgProgramVertexLoadProjectionMatrix(const rs_matrix4x4* proj);
#endif
#endif

/*
 * rsgProgramVertexLoadTextureMatrix: Load the texture matrix for a bound fixed function vertex program
 *
 * DEPRECATED.  Do not use.
 *
 * Load the texture matrix for a currently bound fixed function
 * vertex program. Calling this function with a custom vertex shader
 * would result in an error.
 *
 * Parameters:
 *   tex: texture matrix
 */
#ifndef __LP64__
#if !defined(RS_VERSION) || (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22)
extern void __attribute__((overloadable))
    rsgProgramVertexLoadTextureMatrix(const rs_matrix4x4* tex);
#endif
#endif

/*
 * rsgProgramRasterGetCullMode: Get program raster cull mode
 *
 * DEPRECATED.  Do not use.
 *
 * Get program raster cull mode
 *
 * Parameters:
 *   pr: program raster to query
 */
#ifndef __LP64__
#if (defined(RS_VERSION) && (RS_VERSION >= 16) && (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22))
extern rs_cull_mode __attribute__((overloadable))
    rsgProgramRasterGetCullMode(rs_program_raster pr);
#endif
#endif

/*
 * rsgProgramRasterIsPointSpriteEnabled: Get program raster point sprite state
 *
 * DEPRECATED.  Do not use.
 *
 * Get program raster point sprite state
 *
 * Parameters:
 *   pr: program raster to query
 */
#ifndef __LP64__
#if (defined(RS_VERSION) && (RS_VERSION >= 16) && (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22))
extern bool __attribute__((overloadable))
    rsgProgramRasterIsPointSpriteEnabled(rs_program_raster pr);
#endif
#endif

/*
 * rsgProgramStoreGetBlendDstFunc: Get program store blend destination function
 *
 * DEPRECATED.  Do not use.
 *
 * Get program store blend destination function
 *
 * Parameters:
 *   ps: program store to query
 */
#ifndef __LP64__
#if (defined(RS_VERSION) && (RS_VERSION >= 16) && (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22))
extern rs_blend_dst_func __attribute__((overloadable))
    rsgProgramStoreGetBlendDstFunc(rs_program_store ps);
#endif
#endif

/*
 * rsgProgramStoreGetBlendSrcFunc: Get program store blend source function
 *
 * DEPRECATED.  Do not use.
 *
 * Get program store blend source function
 *
 * Parameters:
 *   ps: program store to query
 */
#ifndef __LP64__
#if (defined(RS_VERSION) && (RS_VERSION >= 16) && (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22))
extern rs_blend_src_func __attribute__((overloadable))
    rsgProgramStoreGetBlendSrcFunc(rs_program_store ps);
#endif
#endif

/*
 * rsgProgramStoreGetDepthFunc: Get program store depth function
 *
 * DEPRECATED.  Do not use.
 *
 * Get program store depth function
 *
 * Parameters:
 *   ps: program store to query
 */
#ifndef __LP64__
#if (defined(RS_VERSION) && (RS_VERSION >= 16) && (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22))
extern rs_depth_func __attribute__((overloadable))
    rsgProgramStoreGetDepthFunc(rs_program_store ps);
#endif
#endif

/*
 * rsgProgramStoreIsColorMaskAlphaEnabled: Get program store alpha component color mask
 *
 * DEPRECATED.  Do not use.
 *
 * Get program store alpha component color mask
 *
 * Parameters:
 *   ps: program store to query
 */
#ifndef __LP64__
#if (defined(RS_VERSION) && (RS_VERSION >= 16) && (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22))
extern bool __attribute__((overloadable))
    rsgProgramStoreIsColorMaskAlphaEnabled(rs_program_store ps);
#endif
#endif

/*
 * rsgProgramStoreIsColorMaskBlueEnabled: Get program store blur component color mask
 *
 * DEPRECATED.  Do not use.
 *
 * Get program store blur component color mask
 *
 * Parameters:
 *   ps: program store to query
 */
#ifndef __LP64__
#if (defined(RS_VERSION) && (RS_VERSION >= 16) && (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22))
extern bool __attribute__((overloadable))
    rsgProgramStoreIsColorMaskBlueEnabled(rs_program_store ps);
#endif
#endif

/*
 * rsgProgramStoreIsColorMaskGreenEnabled: Get program store green component color mask
 *
 * DEPRECATED.  Do not use.
 *
 * Get program store green component color mask
 *
 * Parameters:
 *   ps: program store to query
 */
#ifndef __LP64__
#if (defined(RS_VERSION) && (RS_VERSION >= 16) && (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22))
extern bool __attribute__((overloadable))
    rsgProgramStoreIsColorMaskGreenEnabled(rs_program_store ps);
#endif
#endif

/*
 * rsgProgramStoreIsColorMaskRedEnabled: Get program store red component color mask
 *
 * DEPRECATED.  Do not use.
 *
 * Get program store red component color mask
 *
 * Parameters:
 *   ps: program store to query
 */
#ifndef __LP64__
#if (defined(RS_VERSION) && (RS_VERSION >= 16) && (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22))
extern bool __attribute__((overloadable))
    rsgProgramStoreIsColorMaskRedEnabled(rs_program_store ps);
#endif
#endif

/*
 * rsgProgramStoreIsDepthMaskEnabled: Get program store depth mask
 *
 * DEPRECATED.  Do not use.
 *
 * Get program store depth mask
 *
 * Parameters:
 *   ps: program store to query
 */
#ifndef __LP64__
#if (defined(RS_VERSION) && (RS_VERSION >= 16) && (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22))
extern bool __attribute__((overloadable))
    rsgProgramStoreIsDepthMaskEnabled(rs_program_store ps);
#endif
#endif

/*
 * rsgProgramStoreIsDitherEnabled: Get program store dither state
 *
 * DEPRECATED.  Do not use.
 *
 * Get program store dither state
 *
 * Parameters:
 *   ps: program store to query
 */
#ifndef __LP64__
#if (defined(RS_VERSION) && (RS_VERSION >= 16) && (defined(RS_DECLARE_EXPIRED_APIS) || RS_VERSION <= 22))
extern bool __attribute__((overloadable))
    rsgProgramStoreIsDitherEnabled(rs_program_store ps);
#endif
#endif

#endif // RENDERSCRIPT_RS_GRAPHICS_RSH
