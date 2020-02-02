using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Tile : MonoBehaviour {


    public GameManager gameManager;
    public AudioClip hit;
    AudioSource source;
    Behaviour halo;
	// Use this for initialization
	void Start () {
        source = GetComponent<AudioSource>();
        halo = (Behaviour)source.GetComponent("Halo");
    }
	
	// Update is called once per frame
	void Update () {
		
	}

    private void OnTriggerEnter(Collider other)
    {

        gameManager.AddPoint();
        source.PlayOneShot(hit);
        halo.enabled = true;
        Invoke("SwitchOff", 1);
        

    }

    void SwitchOff()
    {
        halo.enabled = false;
    }

}
