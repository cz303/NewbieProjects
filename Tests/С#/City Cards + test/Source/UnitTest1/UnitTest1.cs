using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Cards;
using System.IO;
using System.Collections.Generic;
using System.Linq;

namespace UnitTest1
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void ResultSort()
        {
            // arrange
            var Journey1 = new Journey();
            Journey1.NewCard(new string[] { "Мельбурн", "Кельн" });
            Journey1.NewCard(new string[] { "Москва", "Париж" });
            Journey1.NewCard(new string[] { "Кельн", "Москва" });

            // act
            Journey1.Sort();

            // assert
            for (int i = 0; i < Journey1.Cities.Count - 1; i++)
            {
                Assert.AreEqual(Journey1.Cities[i]._Destination, Journey1.Cities[i + 1]._Start);
            }
        }

        [TestMethod]
        public void ResultSortFromFile()
        {
            // arrange
            List<Card> Cities = new List<Card>();
            var Journey1 = new Journey();
            List<string> Text = File.ReadAllLines("Cards.txt").ToList();

            // act
            foreach (String item in Text)
                Journey1.NewCard(item.Split('-'));
            Journey1.Sort();

            // assert
            for (int i = 0; i < Journey1.Cities.Count - 1; i++)
            {
                Assert.AreEqual(Journey1.Cities[i]._Destination, Journey1.Cities[i + 1]._Start);
            }


        }
    }
}
