# COP290_Assignments

Assignment-1: 
Expressions being evaluated:
                        Convolution of Matrix with Padding:
                            As matrix multiplication:
                            ./main.out convolution_withpadding_matrixmult matrix1.txt matrix1_numrows matrix2.txt matrix2_numrows
                            As convolution by sliding:
                            ./main.out convolution_withpadding padsize matrix1.txt matrix1_numrows matrix2.txt matrix2_numrows
                        
                        Convolution of Matrix without Padding:
                            As matrix multiplication:
                            ./main.out convolution_withoutpadding_matrixmult matrix1.txt matrix1_numrows matrix2.txt 
                            As convolution by sliding:
                            ./main.out convolution_withoutpadding matrix1.txt matrix1_numrows matrix2.txt
                        
                        Pooling:
                            ./main.out pooling flag matrix1.txt matrix1_numrows fil_size {flag indicates avg or max}
                        
                        RELU Activation:
                            ./main.out relu_activation matrix1.txt matrix1_numrows
                        
                        TANH Activation:
                            ./main.out tanh_activation matrix1.txt matrix1_numrows
                        
Functions being called: Vector_Matrix convolution_matrixmult(kernel_matrix, image)
                        Vector_Matrix convolution(kernel, image)    {If command is withPadding then image is changed by convolution_pad(image, int padding)}
                        Vector_Matrix pooling(image, flag, filesize)
                        Vector_Matrix_Float reluMatrix(image)
                        Vector_Matrix_Float tanhMatrix(image)
                        Vector softmax(vector)
                        Vector sigmoid(vector)
