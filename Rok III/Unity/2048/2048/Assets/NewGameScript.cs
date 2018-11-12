using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NewGameScript : MonoBehaviour {
	public GameManager gameManager;
    void OnMouseDown()
    {
		gameManager.Restart();
    }
}
