//207651027 Tomer Hadar
#include "ex1.h"

/**************
 * Function Name:
   is_big_endian
 * Input:
   the function doesnt get any parameters
 * Function Operation:
   first, we take the number 1, as we know, this number in binary is - 0000 0001 (for 1 byte).
   now, we set a parameter called num of type long with value of 1.
   because char is one byte, i set a poiner from char type, and make it point to the first byte of num,
   as i said, num type is long, so num has 4 or 8 bytes (its depends the machine).
   now we take the byte that the char pointer point at, and we check if the value there is 0 or 1.
   if the value is 0 we can be sure that our machine is working with Big Endian,
   because we know that the pointer point to the first byte of num as its store in the memory,
   on the other hand, if we get value of 1 we know that the machine working with little endian,
   that because its tell us that the MSB is the last Byte, and that how little endian works.
 * @return - the function return 0  if the current machine using little endian to store data,
   and the function return 1 if the current machine using big endian to store data
 **************/
int is_big_endian(){
    //define variable with value 1.
    unsigned long num = 1;
    //pointer to the first byte of num
    char firstByte = *((char*)&num);
    //check if the first byte is 0 or 1.
    if(firstByte == 1){
        return 0;
    }
    return 1;
}
/*********
 * Function name:
   merge_bytes_little
 * @param x - parameter that we take the second half of his bytes.
 * @param y - parameter that we take the first half of his bytes.
 * @param ptr - pointer that point the result variable from the original function.
             (because if we set result in this function, the value of result will vanished as we finish
             with the function).
 * @param size - size of y parameter, its necessary because the size can be different in different machines.
 * Function Operation:
   the function using the fact that: A | 0 = A, that why we set zero variable with value 0
   and than we set a char pointer in 1 byte size that point this zero parameter, now, we using OR operator
   on the bits of the numbers, the first byte of y with 0 and the half byte of x with 0 and puts the
   results in the right byte on the result variable, and we doing that with the ptr pointer that point the result
   variable. like that we change the result variable to be the right result. every iterate we promote
   the pointer ptr to the next byte of result, and promote byte1 and byte2 to point the next bytes int x and y.
   than we finish the function operation and in result variable we have our answer,
   and return it from merge_bytes function.
 */
void merge_bytes_little(unsigned long x, unsigned long int y, char* ptr, int size){
    unsigned long zero = 0;
    //point to one byte with value zero.
    char byte = *((char*)&zero);
    char byte1, byte2;
    for(int i = 0; i < size/2; i++, ptr++){
        //point the first byte of y
        byte1 = *((char*)&y + i);
        //point the middle byte of x
        byte2 = *((char*)&x + (i+size/2));
        //puts in result y byte
        *ptr = (char)(byte1 | byte);
        //puts in another byte of result x byte.
        *(ptr + size/2) = (char)(byte2 | byte);
    }
}
/**********
 * Function name:
   merge_bytes_big
 * @param x - parameter that we take the second half of his bytes.
 * @param y - parameter that we take the first half of his bytes.
 * @param ptr - pointer that point the result variable from the original function.
             (because if we set result in this function, the value of result will vanished as we finish
             with the function).
 * @param size - size of y parameter, its necessary because the size can be different in different machines.
 * Function Operation:
   the function using the fact that: A | 0 = A, that why we set zero variable with value 0
   and than we set a char pointer in 1 byte size that point this zero parameter, now, we using OR operator
   on the bits of the numbers, the last byte of y with 0 and the middle byte of x with 0 and puts the
   results in the right byte on the result variable, and we doing that with the ptr pointer that point the result
   variable. like that we change the result variable to be the right result. every iterate we promote
   the pointer ptr to the next byte of result, and promote byte1 and byte2 to point the next bytes int x and y.
   than we finish the function operation and in result variable we have our answer,
   and return it from merge_bytes function.
 */
void merge_bytes_big(unsigned long x, unsigned long int y, char* ptr, int size){
    unsigned long zero = 0;
    //point to one byte with value zero.
    char byte = *((char*)&zero);
    char byte1, byte2;
    for(int i = size; i >= size/2; i--, ptr--){
        //point to the last byte of y
        byte1 = *((char*)&y + i);
        //point the middle byte of x
        byte2 = *((char*)&x + (i-(size/2)));
        //puts in result y byte
        *(ptr + size) = (char)(byte1 | byte);
        //puts in another byte of result x byte.
        *(ptr + size/2) = (char)(byte2 | byte);
    }
}
/***********
 * Function Name:
   merge_bytes
 * @param x - parameter that we take the second half of his bytes.
 * @param y - parameter that we take the first half of his bytes.
 * Function Operation:
   first, the function checks how the current machine store data, with big endian or little endian,
   and according the result we send data to functions that make the merge between the two numbers.
   if the machine works with Little endian, we send the parameters to function called merge_bytes_little,
   and if the machine works with Big endian, we send the parameters to function called merge_bytes_big.
   we send to this functions the x,y parameters, y size (because there is a different between different machines),
   and we send a pointer to the result parameter so we can change its value from this pointer.
 * @return - returning new number that the first half of his bytes consist of the first half of y bytes,
             and the second half of his bytes consist of the second half of x bytes.
 */
unsigned long merge_bytes(unsigned long x, unsigned long int y){
    //the result of the function.
    unsigned long result;
    //pointer to the first byte of result
    char* ptr = (char*)&result;
    //checking big or little endian
    if(is_big_endian()){
        merge_bytes_big(x, y, ptr, sizeof(y));
        return result;
    }
    merge_bytes_little(x, y, ptr, sizeof(y));
    return result;
}
/**********
 * Function name:
   put_byte
 * @param x - number that we need to change his 8-1-i byte to b.
 * @param b - the byte that we need to put in the 8-1-i byte of x parameter.
 * @param i - calculate with i the 8-i-1 byte that we need to change to be b.
 * Function operation:
   in this function, we set a pointer to point on the first byte of x in the memory and char with value 0.
   than we check if the machine working with big endian or little endian.
   if little endian - we promote ptr to point on the 8-1-i byte of x and replace the value there in b value.
   if big endian - we know that the 8-i-1 byte its actually the i byte because its store in the memory exactly
   the opposite from the little endian, so instead promote ptr to the 8-i-1 byte we need to promote in to the i byte.
   than we using the OR operation to change the given Byte in x to be with b value and return x.
 * @return return x after changing his 8-1-i byte to be b.
 */
unsigned long put_byte(unsigned long x, unsigned char b, int i){
    //pointer to the first byte of x
    char* ptr = (char*)&x;
    char zero = 0;
    if(is_big_endian()){
        //promote the pointer i bytes.
        ptr += i;
    }
    else{
        //promote the pointer 8-i-1 bytes
        ptr += sizeof(x)-i-1;
    }
    //change the byte of x that ptr point of to b.
    *ptr = (char)(b | zero);
    return x;
}