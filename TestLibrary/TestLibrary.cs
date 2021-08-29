using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

namespace TestLibrary
{
    public class TestObject : MonoBehaviour
    {
        public static TestObject instance;
        bool display = false;

        public static void Initialize()
		{
            if(instance != null)
			{
                var newGameObject = new GameObject("TestObject");
                instance = newGameObject.GetComponent<TestObject>();
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
