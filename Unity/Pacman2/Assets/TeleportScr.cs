using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TeleportScr : MonoBehaviour {

	public GameObject otherTeleport;
	public AudioClip teleport;
	public GameObject teleportEffect;
	AudioSource source;

	void Start () {
		source = GetComponent<AudioSource>();
		Instantiate(teleportEffect, transform.position, transform.rotation);
	}
	
	void Update () {
		
	}

	void OnCollisionEnter(Collision col)
    {
		if (col.gameObject.tag == "Player"){
			col.transform.position = new Vector3(-1 * col.gameObject.transform.position.x, col.gameObject.transform.position.y, col.gameObject.transform.position.z);
			source.PlayOneShot(teleport);
		}	
    }
	
}
