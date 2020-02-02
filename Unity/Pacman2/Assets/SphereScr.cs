using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class SphereScr : MonoBehaviour {
	private bool moveUp = true;
	public AudioClip boom;
	private float sphereTime = 15f;
	AudioSource source;
	public PlayerScr player;
	public GameObject explosionEffect;
	public GameObject Upper;
	Animator anim;
	public Image image;
	// Use this for initialization
	void Start () {
		source = GetComponent<AudioSource>();
	}
	
	// Update is called once per frame
	void Update () {
		anim = Upper.GetComponent<Animator>();
		sphereTime -= Time.deltaTime;
		transform.Rotate(new Vector3(0, 30, 0) * Time.deltaTime);
	}

	public void Explode() {
		var expl = Instantiate(explosionEffect, new Vector3(0, 20,0), transform.rotation);
		source.PlayOneShot(boom);
		StartCoroutine("UpperHandManage");
		sphereTime = 15f;
		Destroy(expl,10);
	}

	private IEnumerator UpperHandManage() {
		image.color = new Color32(0,185,0,255);
		player.upperHand += 1;
		yield return new WaitForSeconds(15);
		player.upperHand -= 1;
		if (player.upperHand == 0){
			image.color = new Color32(185,0,0,255);
		}
	}

	private void OnCollisionEnter(Collision col)
    {
		if (col.gameObject.tag == "Player" && TimePassed()){
			Explode();
			anim.SetTrigger("Trigger");
		}
    }

	private bool TimePassed() {
		return sphereTime <= 0;
	}
}
