#include <nine-patch.h>
int draw_nine_patch(nine_patch_image* image, uint32_t content_width, uint32_t content_height,
                    pixel* output_buffer, uint32_t buffer_width, uint32_t buffer_height)
{
    //calculate how much we need to expand.
    uint16_t estimated_width=content_width-(image->content_x_end-image->content_x_begin)+image->width;
    uint16_t estimated_height=content_height-(image->content_y_end-image->content_y_begin)+image->height;
    if(estimated_height>buffer_height||estimated_width>buffer_width) {
        return RESULT_BUFFER_TOO_SMALL;
    }
    uint32_t scale_x_area_end=estimated_width-(image->width-image->content_x_end);
    uint32_t scale_y_area_end=estimated_height-(image->height-image->content_y_end);
    for(uint32_t i=0;i<estimated_height;i++) {
        for(uint32_t j=0;j<estimated_width;j++) {
            //FIXME:SCALE RATIONALLY RATHER THAN USING THE FIRST PIXEL!
            if(j<image->content_x_begin) { //Left side
                if(i<image->content_y_begin) { //Left-up corner
                    output_buffer[i*buffer_width+j] = image->image_without_border[i*image->width+j];
                    continue;
                }
                else if(i>scale_y_area_end) { //Left-down corner
                    output_buffer[i*buffer_width+j] = image->image_without_border[(i-scale_y_area_end+image->content_y_end)*image->width+j];
                    continue;
                }
                else { //left-center corner.
                    output_buffer[i*buffer_width+j] = image->image_without_border[image->content_y_begin*image->width+j];
                    continue;
                }
            }
            else if(j>scale_x_area_end) { //Right side
                if(i<image->content_y_begin) { //Right-up corner
                    output_buffer[i*buffer_width+j] = image->image_without_border[i*image->width+(j-scale_x_area_end+image->content_x_end)];
                    continue;
                }
                else if(i>scale_y_area_end) { //Right-down corner
                    output_buffer[i*buffer_width+j] = image->image_without_border[(i-scale_y_area_end+image->content_y_end)*image->width+(j-scale_x_area_end+image->content_x_end)];
                    continue;
                }
                else { //Right-center corner.
                    output_buffer[i*buffer_width+j] = image->image_without_border[image->content_y_begin*image->width+(j-scale_x_area_end+image->content_x_end)];
                    continue;
                }
            }
            else { //Center
                if(i<image->content_y_begin) { //Center-up corner
                    output_buffer[i*buffer_width+j] = image->image_without_border[i*image->width+image->content_x_begin];
                    continue;
                }
                else if(i>scale_y_area_end) { //Center-down corner
                    output_buffer[i*buffer_width+j] = image->image_without_border[(i-scale_y_area_end+image->content_y_end)*image->width+image->content_x_begin];
                    continue;
                }
                else { //Center corner.
                    output_buffer[i*buffer_width+j] = image->image_without_border[image->content_y_begin*image->width+image->content_x_begin];
                    continue;
                }
            }
        }
    }
    return RESULT_SUCCESS;
}
