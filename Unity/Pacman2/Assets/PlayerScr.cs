using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class PlayerScr : MonoBehaviour {

	public float speed;
	private float verticalRotation;
	public float verticalRotationlimit = 80f;
	public Camera camera2;
	public Camera camera;
	private Rigidbody rb;
	private int score;
	private int bestScore;
	public bool gameOver;
	public TextMeshProUGUI tmp;
	private List<GameObject> cubes = new List<GameObject>();
	public int upperHand;
	public GameObject allCubes;

	public AudioClip music;
	public AudioClip boom;
	public AudioClip bip;
	AudioSource source;
	public GameObject killEffect;
	public GameObject endMenu;
	public TextMeshProUGUI bestScoreText;
	public TextMeshProUGUI currentScoreText;

	void Start () {
		Reset();
		bestScore = 0;
		source = GetComponent<AudioSource>();
		source.PlayOneShot(music);
	}


	
	void Update () {
		if (!gameOver){
			rb.MoveRotation(rb.rotation * Quaternion.Euler(new Vector3(0, Input.GetAxis("Mouse X"), 0)));
			rb.MovePosition(transform.position + (transform.forward * Input.GetAxis("Vertical") * speed) + (transform.right * Input.GetAxis("Horizontal") * speed));

			float horizontalRotation = Input.GetAxis("Mouse X");
			transform.Rotate(0, horizontalRotation, 0);

			verticalRotation -= Input.GetAxis("Mouse Y");
			verticalRotation = Mathf.Clamp(verticalRotation, -verticalRotationlimit, verticalRotationlimit);
			camera.transform.localRotation = Quaternion.Euler(verticalRotation, 0, 0);
		}


	}

	public void Reset(){
		upperHand = 0;
		transform.position = new Vector3(0,1,-32);
		camera.enabled = true;
 		camera2.enabled = false;
		gameOver = false;
		score = 0;
		rb = GetComponent<Rigidbody>();
		verticalRotation = 0;
		Cursor.visible = false;
		Cursor.lockState = CursorLockMode.Locked;
		camera = GetComponentInChildren<Camera>();
		tmp.text = "Score: 0";
		endMenu.SetActive(false);
		ResetCubes();
		cubes.Clear();
	}

	public void End(){
		Cursor.visible = true;
		Cursor.lockState = CursorLockMode.None;
		camera.enabled = false;
		Vector3 offset = camera2.transform.position - transform.position;
		camera2.transform.position = transform.position + offset;
 		camera2.enabled = true;
		gameOver = true;
		if (bestScore < score) {
			bestScore = score;
		}
		endMenu.SetActive(true);
		bestScoreText.text = "Best score: " + bestScore.ToString();
		currentScoreText.text = "Score: " + score.ToString();
	}

	void OnCollisionEnter(Collision collision)
    {
		if(collision.gameObject.tag == "Enemy"){
			if (upperHand > 0){
				var expl = Instantiate(killEffect, collision.contacts[0].point, transform.rotation);
				Destroy(expl,2);
				collision.gameObject.transform.position = new Vector3(0,1,0);
				source.PlayOneShot(boom);
			}
			else{
				End();
			}
		}

		else if (collision.gameObject.tag == "Cube"){
			score += 10;
			tmp.text = "Score: " + score.ToString();
			collision.gameObject.SetActive(false);
			source.PlayOneShot(bip);
		}
    }

	void ResetCubes(){
		foreach (Transform child in allCubes.transform) {
         child.gameObject.SetActive(true);
		}
	}
}	
