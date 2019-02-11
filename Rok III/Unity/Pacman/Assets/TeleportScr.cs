using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TeleportScr : MonoBehaviour {

	public GameObject otherTeleport;

	void Start () {
		
	}
	
	void Update () {
		
	}

	void OnCollisionEnter(Collision col)
    {
		if (col.gameObject.tag == "Player"){
			col.transform.position = new Vector3(-1 * col.gameObject.transform.position.x, col.gameObject.transform.position.y, col.gameObject.transform.position.z);
		}	
    }
	
}
