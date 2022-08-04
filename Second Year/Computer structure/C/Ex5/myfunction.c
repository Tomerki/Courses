//207651027 Tomer Hadar

//macro function that defined while compiling the program and not in runtime.
#define low(sum) (sum < 0 ? 0 : sum < 255 ? sum : 255)

/**
 * in this program, where ever i saw an multiply action i tried to convert it to +/- action that its cheaper.
 * i really reduce a functions calls and saved a loops that was'nt necessary.
 * i canceled a lot of functions that was unnecessary and instead using those function i just implemented
 * the same logic inside the same function.
 *
 * in general, i tried to minimize as much as i can a memory references, an unnecessary loops and function calls,
 * i also used loop unrolling in some function.
 */


typedef struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} pixel;

typedef struct {
    int red;
    int green;
    int blue;
} pixel_sum;

/**
 *
 * @param dim - dimension of the matrix that represent the image.
 * @param src - source matrix with pixels in every index.
 * @param dst - the matrix that we puts inside the new values after the smooth and filter.
 * @param kernelSize - the size of the matrix that we go over with her on the image.
 * @param kernel - the matrix that we use to make the image sharper.
 * @param kernelScale - the size of the scale of the indexes that we go over(half of the kernelsize).
 *
 * in this function i did exactly as i did in the smoothNoFilter function but with a filter.
 * means, i also here convert the two loops to a permanent numbers of action that the loops did.
 * this help us to save jump calls and parameters initialize.
 *
 */

void smooth(int dim, pixel *src, pixel *dst, int kernelSize, int kernel[kernelSize][kernelSize], int kernelScale) {
    int index2, pixel_size, pixel_size1, pixel_size2;
    pixel_sum sum;
    pixel current_pixel, pixel_index, pixel_index1, p1, p2, p3;
    int min_row, min_col, max_row, max_col;
    int min_intensity, max_intensity;
    int ker1, ker2;
    //takes only 1 time the value in the kernel because all the indexes equal but the index 1,1.
    ker1 = kernel[0][0];
    ker2 = kernel[1][1];
    int i, j, start, index;
    start = kernelSize / 2;
    int size = dim - start;
    for (i = start ; i < size ; i++) {
        index = i * dim;
        for (j = start ; j < size ; j++) {

            min_intensity = 766; // arbitrary value that is higher than maximum possible intensity, which is 255*3=765
            max_intensity = -1; // arbitrary value that is lower than minimum possible intensity, which is 0
            sum.red = sum.green = sum.blue = 0;
            //update the index, that its equal to promote ii variable in the original code.
            index2 = (i-1) * dim;
            p1 = src[index2 + j - 1];
            p2 = src[index2 + j];
            p3 = src[index2 + j + 1];
            sum.red += (int) (ker1 * (p1.red + p2.red + p3.red));
            sum.green += (int) (ker1 * (p1.green  + p2.green  + p3.green));
            sum.blue += (int) (ker1 * (p1.blue + p2.blue + p3.blue));
            //make the filter action.
            pixel_size = (int)(p1.red + p1.green + p1.blue);
            //this like the two loops while ii = i-1 and jj = j-1
            if (pixel_size <= min_intensity) {
                min_intensity = pixel_size;
                min_row = i - 1;
                min_col = j - 1;
            }
            if (pixel_size > max_intensity) {
                max_intensity = pixel_size;
                max_row = i - 1;
                max_col = j - 1;
            }
            //promote jj to jj = j.
            pixel_size1 = (int)(p2.red + p2.green + p2.blue);
            if (pixel_size1 <= min_intensity) {
                min_intensity = pixel_size1;
                min_row = i - 1;
                min_col = j;
            }
            if (pixel_size1 > max_intensity) {
                max_intensity = pixel_size1;
                max_row = i - 1;
                max_col = j;
            }

            pixel_size2 = (int)(p3.red + p3.green + p3.blue);
            if (pixel_size2 <= min_intensity) {
                min_intensity = pixel_size2;
                min_row = i - 1;
                min_col = j + 1;
            }
            if (pixel_size2 > max_intensity) {
                max_intensity = pixel_size2;
                max_row = i - 1;
                max_col = j + 1;
            }

            index2 += dim;
            p1 = src[index2 + j - 1];
            p2 = src[index2 + j];
            p3 = src[index2 + j + 1];
            sum.red += (int) (ker1 * (p1.red + p3.red) + (p2.red * ker2));
            sum.green += (int) (ker1 * (p1.green + p3.green) + (p2.green * ker2));
            sum.blue += (int) (ker1 * (p1.blue + p3.blue) + (p2.blue * ker2));
            //now promote ii = i and jj loop start from the begining.
            pixel_size = (int)(p1.red + p1.green + p1.blue);
            if (pixel_size <= min_intensity) {
                min_intensity = pixel_size;
                min_row = i;
                min_col = j - 1;
            }
            if (pixel_size > max_intensity) {
                max_intensity = pixel_size;
                max_row = i;
                max_col = j - 1;
            }

            pixel_size1 = (int)(p2.red + p2.green + p2.blue);
            if (pixel_size1 <= min_intensity) {
                min_intensity = pixel_size1;
                min_row = i;
                min_col = j;
            }
            if (pixel_size1 > max_intensity) {
                max_intensity = pixel_size1;
                max_row = i;
                max_col = j;
            }

            pixel_size2 = (int)(p3.red + p3.green + p3.blue);
            if (pixel_size2 <= min_intensity) {
                min_intensity = pixel_size2;
                min_row = i;
                min_col = j + 1;
            }
            if (pixel_size2 > max_intensity) {
                max_intensity = pixel_size2;
                max_row = i;
                max_col = j + 1;
            }


            index2 += dim;
            p1 = src[index2 + j - 1];
            p2 = src[index2 + j];
            p3 = src[index2 + j + 1];
            sum.red += (int) (ker1 * (p1.red + p2.red + p3.red ));
            sum.green += (int) (ker1 * (p1.green + p2.green + p3.green));
            sum.blue += (int) (ker1 * (p1.blue + p2.blue + p3.blue));

            pixel_size = (int)(p1.red + p1.green + p1.blue);
            if (pixel_size <= min_intensity) {
                min_intensity = pixel_size;
                min_row = i + 1;
                min_col = j - 1;
            }
            if (pixel_size > max_intensity) {
                max_intensity = pixel_size;
                max_row = i + 1;
                max_col = j - 1;
            }

            pixel_size1 = (int)(p2.red + p2.green + p2.blue);
            if (pixel_size1 <= min_intensity) {
                min_intensity = pixel_size1;
                min_row = i + 1;
                min_col = j;
            }
            if (pixel_size1 > max_intensity) {
                max_intensity = pixel_size1;
                max_row = i + 1;
                max_col = j;
            }

            pixel_size2 = (int)(p3.red + p3.green + p3.blue);
            if (pixel_size2 <= min_intensity) {
                min_intensity = pixel_size2;
                min_row = i + 1;
                min_col = j + 1;
            }
            if (pixel_size2 > max_intensity) {
                max_intensity = pixel_size2;
                max_row = i + 1;
                max_col = j + 1;
            }

            //make the sum action here instead of doing it in a new function.
            pixel_index = src[min_row*dim + min_col];
            pixel_index1 = src[max_row*dim+max_col];
            sum.red -= (int)(pixel_index.red + pixel_index1.red);
            sum.green -= (int)(pixel_index.green + pixel_index1.green);
            sum.blue -= (int)(pixel_index.blue + pixel_index1.blue);
            //assign_sum_to_pixel - Truncates pixel's new value to match the range [0,255]
            current_pixel.red = (unsigned char) low(sum.red / kernelScale);
            current_pixel.green = (unsigned char) low(sum.green / kernelScale);
            current_pixel.blue = (unsigned char) low(sum.blue / kernelScale);
            dst[index + j] = current_pixel;
        }
    }
}

/**
 *
 * @param dim - dimension of the matrix that represent the image.
 * @param src - source matrix with pixels in every index.
 * @param dst - the matrix that we puts inside the new values after the smooth.
 * @param kernelSize - the size of the matrix that we go over with her on the image.
 * @param kernel - the matrix that we use to make the image sharper.
 * @param kernelScale - the size of the scale of the indexes that we go over(half of the kernelsize).
 *
 *
 * i notice that in the original code the smooth function sends all the data to the applykernel function,
 * and this action took time and cost us a lot of function calls, but actually the function applykernel
 * run 2 loops that always runs 9 times, so i passed the applykernel function and those loop and turns it to
 * regular code without loop because those loops activated a permanent time every time, its means that
 * we have a permanent number of actions to make every time, so by canceling the loops we saved jump calls,
 * assignment of variables and multiply actions.
 */

void smoothNoFilter(int dim, pixel *src, pixel *dst, int kernelSize, int kernel[kernelSize][kernelSize], int kernelScale){
    int i, j,start, index, size, index2;
    int ker1, ker2;
    //takes only 1 time the value in the kernel because all the indexes equal but the index 1,1.
    ker1 = kernel[0][0];
    ker2 = kernel[1][1];
    pixel_sum sum;
    pixel pixel_result, p1, p2, p3;
    start = kernelSize / 2;
    size = dim - start;
    for (i = start ; i < size ; i++) {
        index = i * dim;
        for (j = start ; j < size ; j++) {
            //every iteration a new sum.
            sum.red = sum.green = sum.blue = 0;

            index2 = (i-1) * dim;
            //saved a memory access by access the index only once.
            p1 = src[index2 + j - 1];
            p2 = src[index2 + j];
            p3 = src[index2 + j + 1];
            sum.red += (int) (ker1 * (p1.red + p2.red + p3.red));
            sum.green += (int) (ker1 * (p1.green  + p2.green  + p3.green));
            sum.blue += (int) (ker1 * (p1.blue + p2.blue + p3.blue));

            //update the index, that its equal to promote ii variable in the original code.
            index2 += dim;
            p1 = src[index2 + j - 1];
            p2 = src[index2 + j];
            p3 = src[index2 + j + 1];
            sum.red += (int) (ker1 * (p1.red + p3.red) + (p2.red * ker2));
            sum.green += (int) (ker1 * (p1.green + p3.green) + (p2.green * ker2));
            sum.blue += (int) (ker1 * (p1.blue + p3.blue) + (p2.blue * ker2));

            index2 += dim;
            p1 = src[index2 + j - 1];
            p2 = src[index2 + j];
            p3 = src[index2 + j + 1];
            //assign the pixels sum.
            sum.red += (int) (ker1 * (p1.red + p2.red + p3.red ));
            sum.green += (int) (ker1 * (p1.green + p2.green + p3.green));
            sum.blue += (int) (ker1 * (p1.blue + p2.blue + p3.blue));

            //assign_sum_to_pixel - Truncates pixel's new value to match the range [0,255]
            pixel_result.red = (unsigned char) low(sum.red / kernelScale);
            pixel_result.green = (unsigned char) low(sum.green / kernelScale);
            pixel_result.blue = (unsigned char) low(sum.blue / kernelScale);

            //puts the new value of the pixel in the dest matrix.
            dst[index + j] = pixel_result;
        }
    }
}

/**
 *
 * @param image - the image we need to sharpen and filter.
 * @param kernelSize - the size of the matrix that we go over with her on the image.
 * @param kernel - the matrix that we use to make the image sharper.
 * @param kernelScale - the size of the scale of the indexes that we go over(half of the kernelsize).
 * @param filter - boolean variable that indicates if we need to make a filter to the image.
 *
 * this function takes the image and turns the chars in every 3 indexes to one pixel,
 * as we know, every 3 indexes in the image matrix represent one pixel.
 * the we save the new matrix with the pixels in another matrix.
 *
 * after doing so, we check the filter variable value, if its true, we sending the data that we need
 * to smooth function that make a smooth and filter, else, if its false, we sending the data
 * to smoothNoFilter function that only make a smooth without filter.
 *
 * after we finish this part we just puts in the original matrix of the image the new pixels value
 * after we made a smooth or smooth and filter.
 *
 * to reduce the runtime we did all the conversions from chars to pixels and pixels to char in this function,
 * by doing so we saved a functions calls and memory on the call stack, we also saved a lot of
 * variables assignment to registers for passing parameters.
 * i also merged thw loops of the chars to pixels with the copy loops.
 */
void doConvolution(Image *image, int kernelSize, int kernel[kernelSize][kernelSize], int kernelScale, int withFilter) {
    int row, col, dataPlace, rowNum, index, index1;
    unsigned long mySize = m*n*sizeof(pixel);
    pixel* pixelsImg = malloc(mySize);
    pixel* backupOrg = malloc(mySize);
    //variable to save a memory references.
    pixel p, p1, p2, p3;

    for (row = 0, rowNum = 0 ; row < m; row++, rowNum += n) {
        //promote col by 2 every iteration for using in differents unit of the processor in parallel.
        //this will work only on superscalar processors. (loop unrolling).
        for (col = 0 ; col < n - 1 ; col+=2) {
            dataPlace = (rowNum + rowNum + rowNum + col + col + col);
            index = rowNum + col;
            index1 = rowNum + col + 1;
            p.red = p2.red = image->data[dataPlace];
            p.green = p2.green = image->data[dataPlace + 1];
            p.blue = p2.blue = image->data[dataPlace + 2];
            p1.red = p3.red = image->data[dataPlace + 3];
            p1.green = p3.green = image->data[dataPlace + 4];
            p1.blue = p3.blue = image->data[dataPlace + 5];
            //after assign values to local variable we puts it inside the memory, by doing so we saved
            //a lot of memory access.
            backupOrg[index] = p;
            backupOrg[index1] = p1;
            pixelsImg[index] = p2;
            pixelsImg[index1] = p3;


        }
    }

    //if filter true we go to smooth and filter, else only smooth.
    if(withFilter)
        smooth(m, backupOrg, pixelsImg, kernelSize, kernel, kernelScale);
    else
        smoothNoFilter(m, backupOrg, pixelsImg, kernelSize, kernel, kernelScale);

    for (row = 0, rowNum = 0 ; row < m; row++, rowNum += n) {
        //promote col by 2 every iteration for using in differents unit of the processor in parallel.
        //this will work only on superscalar processors. (loop unrolling).
        for (col = 0 ; col < n - 1 ; col+=2) {
            dataPlace = rowNum + rowNum + rowNum + col + col + col;
            index = rowNum + col;
            index1 = rowNum + col + 1;
            p = pixelsImg[index];
            p1 = pixelsImg[index1];
            image->data[dataPlace] = p.red;
            image->data[dataPlace + 1] = p.green;
            image->data[dataPlace + 2] = p.blue;
            image->data[dataPlace + 3] = p1.red;
            image->data[dataPlace + 4] = p1.green;
            image->data[dataPlace + 5] = p1.blue;
        }
    }
    free(pixelsImg);
    free(backupOrg);
}

void myfunction(Image *image, char* srcImgpName, char* blurRsltImgName, char* sharpRsltImgName, char* filteredBlurRsltImgName, char* filteredSharpRsltImgName, char flag) {

    int blurKernel[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};

    int sharpKernel[3][3] = {{-1,-1,-1},{-1,9,-1},{-1,-1,-1}};

    if (flag == '1') {
        doConvolution(image, 3, blurKernel, 9, 0);

        writeBMP(image, srcImgpName, blurRsltImgName);

        doConvolution(image, 3, sharpKernel, 1, 0);

        writeBMP(image, srcImgpName, sharpRsltImgName);
    } else {

        doConvolution(image, 3, blurKernel, 7, 1);

        writeBMP(image, srcImgpName, filteredBlurRsltImgName);

        doConvolution(image, 3, sharpKernel, 1, 0);

        writeBMP(image, srcImgpName, filteredSharpRsltImgName);
    }
}