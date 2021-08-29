using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using UnityEngine;

namespace TestLibrary
{
    public class TestLibrary
    {
        public static void Init()
		{
            using (StreamWriter @out = new StreamWriter(new FileStream("ExampleAssembly.log", FileMode.OpenOrCreate)))
            {
                //Let us know everything is okay and we're up and running.
                @out.WriteLine("Injection worked! Bye!");
                @out.Flush();
                @out.Close();
            }
            Hack.TestHack.InitializeHack();
        }
    }
}
