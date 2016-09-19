/*==============================================================================
	cgim application
	copyright chris g. willcocks MIT license
	written in C89 because modern stuff sucks
==============================================================================*/

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define CG_IMAGE_IMPLEMENTATION
#define CG_IMAGE_GL_IMPLEMENTATION
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800
#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <time.h>
#include "../deps/gl/glew.h"
#include "../deps/gl/glfw3.h"
#include "nk_nuklear.h"
#include "nk_glfw3.h"
#include "stb_image.h"
#include "cg_image.h"
#include "cg_image_gl.h"

static void errorCallback(int e, const char* d)
{
   printf("Error %d: %s\n", e, d);
}

int glfwSetWindowCenter(GLFWwindow * window)
{
   int sx = 0, sy = 0;
   int px = 0, py = 0;
   int mx = 0, my = 0;
   int monitor_count = 0;
   int best_area = 0;
   int final_x = 0, final_y = 0;
   int j;

   GLFWmonitor ** m = NULL;

   if(!window)
      return 0;

   glfwGetWindowSize( window , &sx, &sy );
   glfwGetWindowPos( window , &px, &py );

   m = glfwGetMonitors( &monitor_count );

   if(!m)
      return 0;

   for (j=0; j<monitor_count; ++j)
   {
      const GLFWvidmode * mode = NULL;
      int minX;
      int minY;
      int maxX;
      int maxY;
      int area;

      glfwGetMonitorPos(m[j], &mx, &my);
      mode = glfwGetVideoMode(m[j]);

      if( !mode )
         continue;

      minX = mx>px?mx:px;
      minY = my>py?my:py;

      maxX = mx+mode->width <px+sx?mx+mode->width :px+sx;
      maxY = my+mode->height<py+sy?my+mode->height:py+sy;

      area = (maxX-minX>0?maxX-minX:0)*(maxY-minY>0?maxY-minY:0);
      if (area>best_area)
      {
         final_x = mx + (mode->width-sx)/2;
         final_y = my + (mode->height-sy)/2;
         best_area = area;
      }
   }

   if(best_area)
      glfwSetWindowPos(window , final_x , final_y);
   else
   {
      GLFWmonitor * primary = glfwGetPrimaryMonitor( );
      if( primary )
      {
         const GLFWvidmode * desktop = glfwGetVideoMode( primary );

         if( desktop )
            glfwSetWindowPos( window , (desktop->width-sx)/2 , (desktop->height-sy)/2 );
         else
            return 0;
      }
      else
         return 0;
   }
   return 1;
}

int main()
{
   /* platform */
   static GLFWwindow* win = NULL;
   int width = 0, height = 0;
   struct nk_context *ctx = NULL;
   struct cg_image* im = NULL;
   struct cg_image* dst = NULL;
   struct nk_image tex;
	unsigned char *data = NULL;


   /* glfw */
   glfwSetErrorCallback(errorCallback);
   if (!glfwInit())
   {
      fprintf(stdout, "[GFLW] failed to init!\n");
      exit(1);
   }
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
#ifdef __APPLE__
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
   win = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "CGIM", NULL, NULL);
   glfwSetWindowCenter(win);
   glfwMakeContextCurrent(win);
   glfwGetWindowSize(win, &width, &height);

   /* openGL */
   glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
   glewExperimental = 1;
   if (glewInit() != GLEW_OK)
   {
      fprintf(stderr, "Failed to setup GLEW\n");
      exit(1);
   }

   ctx = nk_glfw3_init(win, NK_GLFW3_INSTALL_CALLBACKS);
   {
      struct nk_font_atlas *atlas;
      nk_glfw3_font_stash_begin(&atlas);
      nk_glfw3_font_stash_end();
   }

   /* image */
   im = cg_image_load("../data/lena2D.png");

   /*cg_image_rgb_to_gray(im);*/
	dst = cg_image_clone(im, 1);
	tex = nk_image_id(cg_image_bind(im));
   cg_image_free(im);

	data = (unsigned char*)dst->data;

	printf("dst: %i\n", data[512*500]);
	/*cg_image_free(dst);*/

   glfwShowWindow(win);
   while (!glfwWindowShouldClose(win))
   {
      /* input */
      glfwPollEvents();
      nk_glfw3_new_frame();

      /* gui */
      {
         struct nk_panel layout;
         if (nk_begin(ctx, &layout, "Image Window", nk_rect(50, 50, 230, 250), NK_WINDOW_BORDER|NK_WINDOW_SCALABLE|NK_WINDOW_TITLE))
         {
            nk_layout_row_dynamic(ctx, 25, 1);
            nk_label(ctx, "hi", NK_TEXT_LEFT);

            nk_layout_row_static(ctx, 512, 512, 1);
            nk_image(ctx, tex);
         }
         nk_end(ctx);
      }

      glfwGetWindowSize(win, &width, &height);
      glViewport(0, 0, width, height);
      glClear(GL_COLOR_BUFFER_BIT);
      glClearColor(28/255.0f, 48/255.0f, 62/255.0f, 1.0f);
      /* end of gui update */

      nk_glfw3_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
      glfwSwapBuffers(win);
   }

   nk_glfw3_shutdown();
   glfwTerminate();
   return 0;
}
