using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static System.Console;

namespace First
{
    class Program
    {
        static void Main(string[] args)
        {
            int number=-1; string result =""; ulong fact=1;

            again:
            Write("Enter the number:");
            if (!(int.TryParse(ReadLine(), out number)) || number < 0) result = "Wrong input";
            else
            {
                fact = factorial((ulong)number);
                if (fact == 0) result = "Out of range";
                else result = String.Format ("{0:N0}",fact);
            }
           WriteLine("Factorial of {0}! = {1}", number, result);

            answer:
            Write("\r" + new string(' ', Console.WindowWidth-1) + "\r");
            Write("Again? <y/n>:");

            switch (ReadLine())
            {
                case "Y": WriteLine();  goto again;
                case "y": WriteLine();  goto again;
                case "n": return;
                case "N": return;
                default: Console.SetCursorPosition(0, Console.CursorTop-1); goto answer;
            }

        }

        static ulong factorial(ulong result)
        {
            if ( result == 0 ) return 1;
            result = result * factorial(result-1);
            if ( result > Int64.MaxValue) return 0;
            return result;
        }
    }
}
