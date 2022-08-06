//Tomer Hadar
#include "ex2.h"
/*********
 * Function Name:
   NumberValueMagnitude.
 @param a - number with two's complement value.
 @return - the function return the value of a to his magnitude value according the binary representation.
 * Function Operation:
   the function convert the value of a to his magnitude value according
   the binary representation. if a is negative we are doing it by turn of the 32 bit and than multiply
   the number by -1.
   if a is positive so his two's complement value identical to his magnitude value so we dont need to change anything.
 *********/
magnitude NumberValueMagnitude(magnitude a){
    if((a >> 31) == 1){
        a = 0;
    }
    if(a < 0)
        return (-(a & 0x7fffffff));
    return a;
}
/********
 * Function Name:
   multi.
 * @param a - number that represent the two's complement value but the binary representation is magnitude.
 * @param b - number that represent the two's complement value but the binary representation is magnitude.
 * @return - return the multiplication of a and b after converting those numbers value to magnitude
 *           and then converting the result to magnitude value and return it.
 * Function Operation:
   the function uses NumberValueMagnitude function to convert the numbers to magnitude value and then checks if
   there is an Over/Under flow. if after the multiplication of a and b we get an under/over flow
   in the two's complement representation then we convert the over/under flow result by the two's complement
   to magnitude value without an over/under flow.
 */
magnitude multi(magnitude a, magnitude b){
    magnitude result;
    //checking for underflow.
    if((a < 0 && b > 0) || (a > 0 && b < 0)){
        result = NumberValueMagnitude(NumberValueMagnitude(a) * NumberValueMagnitude(b));
        //in case a<0 and b>0 or the opposite, if result is positive after multiplication a and b, its underflow.
        if(result > 0){
            return -result;
        }
    }
    //checking for overflow.
    if(a < 0 && b < 0){
        result = NumberValueMagnitude(NumberValueMagnitude(a) * NumberValueMagnitude(b));
        //in case a and b are negative, if result is negative after multiplication a and b, its overflow.
        if(result < 0){
            return -result;
        }
    }
    //checking for overflow.
    if(a > 0 && b > 0){
        result = NumberValueMagnitude(NumberValueMagnitude(a) * NumberValueMagnitude(b));
        //in case a and b are positive, if result is negative after multiplication a and b, its overflow.
        if(result < 0){
            return -result;
        }
    }
    return NumberValueMagnitude(NumberValueMagnitude(a) * NumberValueMagnitude(b));
}
/*****
 *  Function Name:
    sub.
 * @param a -  number that represent the two's complement value but the binary representation is magnitude.
 * @param b -  number that represent the two's complement value but the binary representation is magnitude.
 * @return - return the subtraction of a and b after converting those numbers value to magnitude
 *           and then converting the result to magnitude value and return it.
 * Function Operation:
   the function uses NumberValueMagnitude function to convert the numbers to magnitude value and then checks if
   there is an Over/Under flow. if after the subtraction of a and b we get an under/over flow
   in the two's complement representation then we convert the over/under flow result by the two's complement
   to magnitude value without an over/under flow.
 */
magnitude sub(magnitude a, magnitude b){
    //checking for overflow.
    if(a > 0 && b < 0){
        if((NumberValueMagnitude(a) - NumberValueMagnitude(b)) < 0){
            return -NumberValueMagnitude(NumberValueMagnitude(a) - NumberValueMagnitude(b));
        }
    }
    //checking for underflow.
    else if(a < 0 && b > 0){
        if(NumberValueMagnitude(a) - NumberValueMagnitude(b) > 0){
            return -NumberValueMagnitude((NumberValueMagnitude(a) - NumberValueMagnitude(b)));
        }
    }
    return NumberValueMagnitude(NumberValueMagnitude(a) - NumberValueMagnitude(b));
}
/*****
 *  Function Name:
    add.
 * @param a -  number that represent the two's complement value but the binary representation is magnitude.
 * @param b -  number that represent the two's complement value but the binary representation is magnitude.
 * @return return the addition of a and b after converting those numbers value to magnitude
 *           and then converting the result to magnitude value and return it.
 * Function Operation:
   the function uses NumberValueMagnitude function to convert the numbers to magnitude value and then checks if
   there is an Over/Under flow. if after the addition of a and b we get an under/over flow
   in the two's complement representation then we convert the over/under flow result by the two's complement
   to magnitude value without an over/under flow.
 *****/
magnitude add(magnitude a, magnitude b){
    //checking for underflow.
    if(a < 0 && b < 0){
        if(NumberValueMagnitude(a) + NumberValueMagnitude(b) > 0){
            return -NumberValueMagnitude((NumberValueMagnitude(a) + NumberValueMagnitude(b)));
        }
    }
    //checking for overflow.
    else if(a > 0 && b > 0){
        if(NumberValueMagnitude(a) + NumberValueMagnitude(b) < 0){
            return -NumberValueMagnitude(NumberValueMagnitude(a) + NumberValueMagnitude(b));
        }
    }
    return NumberValueMagnitude(NumberValueMagnitude(a) + NumberValueMagnitude(b));
}
/*****
 * Function Name:
   equal.
 * @param a -  number that represent the two's complement value but the binary representation is magnitude.
 * @param b -  number that represent the two's complement value but the binary representation is magnitude.
 * @return - return 0 if numbers in magnitude value are unequal and 1 if they equal.
 * Function Operation:
   the function uses NumberValueMagnitude function to convert the numbers to magnitude value and then
   make a compare between the two numbers.
 */
int equal(magnitude a, magnitude b){
    if(NumberValueMagnitude(a) == NumberValueMagnitude(b))
        return 1;
    return 0;
}
/*****
 * Function Name:
   greater.
 * @param a -  number that represent the two's complement value but the binary representation is magnitude.
 * @param b -  number that represent the two's complement value but the binary representation is magnitude.
 * @return - return 1 if the magnitude value of a is greater than the magnitude value of b.
             if the magnitude value of b is greater than the magnitude value of a the function return 0.
 */
int greater(magnitude a, magnitude b){
    if(NumberValueMagnitude(a) > NumberValueMagnitude(b))
        return 1;
    return 0;
}
