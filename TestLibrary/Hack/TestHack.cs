using System;
using UnityEngine;

namespace TestLibrary.Hack
{
	class TestHack : MonoBehaviour
	{

		public static TestHack instance;
		bool display = false;

		public static void InitializeHack()
		{
			if(instance == null)
			{
				var newGameObject = new GameObject("TestObject");
				instance = newGameObject.AddComponent<TestHack>();
				DontDestroyOnLoad(newGameObject);

				//Probably not needed
				instance.gameObject.SetActive(true);
				instance.enabled = true;
				Meebey.SmartIrc4net.IrcClient client = new Meebey.SmartIrc4net.IrcClient();
			}
		}

		private static void Client_OnConnected(object sender, System.EventArgs e)
		{
			Debug.Log(e);
		}

		void Update()
		{
			if (Input.GetKeyDown(KeyCode.F10))
			{
				display = !display;
			}
		}

		void OnGUI()
		{
			if (display)
			{
				GUI.Box(new Rect(20, 20, 150, 400), "Sui sucks at coding!");
			}
		}
	}
}
