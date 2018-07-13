using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Cards
{
    public class Card // Карточка
    {
        public Card(string Start, string Destination)
        {
            this._Start = Start;
            this._Destination = Destination;
        }

        public string _Start { get; set; }
        public string _Destination { get; set; }

        public override string ToString()
        {
            return _Start + " -> " + _Destination;
        }

    }


    public class Journey // Путешествие с карточками
    {
        public string _ClassName { get; set; }
        public List<Card> Cities = new List<Card>();

        public Journey(string name)
        {
            _ClassName = name;
        }
        public Journey()
        {
            _ClassName = "unnamed";
        }

        public void NewCard(string[] City)
        {
            Cities.Add(new Card(City[0], City[1]));
        }

        public void Print()
        {
            foreach (Card item in Cities)
                Console.WriteLine(item);
        }

        static void Swap(IList<Card> list, int index1, int index2)
        {
            Card tmp = list[index1];
            list[index1] = list[index2];
            list[index2] = tmp;
        }

        public static List<Card> Sort(List<Card> list)
        {
            List<Card> Cards = list;

            for (int i = 0; i < Cards.Count - 1; i++)
            {
                for (int q = i; q < Cards.Count - 2; q++)
                {
                    if (Cards[i]._Destination == Cards[i + 1]._Start)
                    {
                        break;
                    }
                    if (Cards[i]._Destination == Cards[q + 2]._Start)
                    {
                        Swap(Cards, i + 1, q + 2);
                        break;
                    }
                }
            }
            return Cards;
        }

        public void Sort()
        {
            Cities = Sort(Cities);
        }

    }

    class Program
    {
        static void Main(string[] args)
        {
            string cities;
            var Journey1 = new Journey();

            /* Заполнение списка карточек вводом с клавиатуры*/
            Console.Write("Enter name of the Journey:\n");
            Journey1._ClassName = Console.ReadLine();
            Console.Write("Enter new card (eg 'City-City', enter 'go' to sort):\n");

        again:
            cities = Console.ReadLine();

            if (cities != "go")
            {
                // Проверка на правильный результат ввода
                if (cities.Split('-').Length == 2)
                    // Добавление новой пары
                    Journey1.NewCard(cities.Split('-'));
                else
                {
                    // Возврат строки и очистка неправильного ввода
                    Console.Write("Wrong input");
                    Console.SetCursorPosition(0, Console.CursorTop - 1);
                    Console.Write("\r" + new string(' ', Console.WindowWidth - 1) + "\r");
                }
                Console.Write("\r" + new string(' ', Console.WindowWidth - 1) + "\r");
                goto again;
            }
            /* Конец заполнение списка карточек */

            // Сортировка и вывод списка
            Journey1.Sort();
            Console.WriteLine("\n Sorted " + Journey1._ClassName + ": \n");
            Journey1.Print();

            Console.ReadLine();
        }

    }

}
