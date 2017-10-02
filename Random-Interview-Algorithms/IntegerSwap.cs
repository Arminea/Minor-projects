using System;
using System.Collections.Generic;

public class IntegerSwap
{
   public static void Main()
   {
   	  Rotate(1234);
      Rotate(-9876);
      Rotate(int.MaxValue);
      Rotate(int.MinValue);
   }

   private static void Rotate(int num)
   {
   		Console.WriteLine("Number: " + num);

   		int rotNum = 0;

   		checked
		{
		    try 
		    {
		    	bool isNegative = false;

		   		if(num < 0) {
		   			isNegative = true;
		   			num = Math.Abs(num);
		   		}

		   		int numLen = Math.Floor((decimal) num).ToString().Length - 1;

		   		do {
				  	rotNum += (num % 10) * ((int) Math.Pow(10, numLen));
				    num /= 10;
				    numLen--;
				} while (num > 0);

				if(isNegative)
					rotNum = 0 - rotNum;
			}
			catch (OverflowException) 
		    {
		        Console.WriteLine("OverflowException. Rotated number is not in integer range.");
		        return;
		    }
		}     

		Console.WriteLine("Rotated number: " + rotNum);
   }

}