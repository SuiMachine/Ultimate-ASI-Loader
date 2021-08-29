using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using UnityEngine;

namespace TestLibrary
{
    public class TestLibrary : MonoBehaviour
    {
        public static TestLibrary instance;
        bool display = false;

        public static void Initialize()
		{
            if(instance != null)
			{
                using (StreamWriter @out = new StreamWriter(new FileStream("ExampleAssembly.log", FileMode.OpenOrCreate)))
                {

                    //Let us know everything is okay and we're up and running.
                    @out.WriteLine("Injection worked! Bye!");
                    @out.Flush();
                    @out.Close();

                }

                var newGameObject = new GameObject("TestObject");
                instance = newGameObject.GetComponent<TestLibrary>();
                DontDestroyOnLoad(newGameObject);

                //Probably not needed
                instance.gameObject.SetActive(true);
                instance.enabled = true;
            }
		}

        void Update()
        {
            if(Input.GetKeyDown(KeyCode.F10))
			{
                display = !display;
			}
        }

        void OnGUI()
		{
            if(display)
			{
                GUI.Box(new Rect(20, 20, 150, 400), "OMGZ");
                GUI.Button(new Rect(50, 50, 140, 140), "WoRKZ");
            }
        }
    }
}
