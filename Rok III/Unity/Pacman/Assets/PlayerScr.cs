using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class PlayerScr : MonoBehaviour {

	public float speed;
	private float verticalRotation;
	public Camera camera2;
	public Camera camera;
	private Rigidbody rb;
	private int score;
	private int bestScore;
	public bool gameOver;
	public TextMeshProUGUI tmp;
	private List<GameObject> cubes = new List<GameObject>();

	public GameObject endMenu;
	public TextMeshProUGUI bestScoreText;
	public TextMeshProUGUI currentScoreText;

	void Start () {
		Reset();
		bestScore = 0;
	}


	
	void Update () {
		if (!gameOver){
			rb.MoveRotation(rb.rotation * Quaternion.Euler(new Vector3(0, Input.GetAxis("Mouse X"), 0)));
			rb.MovePosition(transform.position + (transform.forward * Input.GetAxis("Vertical") * speed) + (transform.right * Input.GetAxis("Horizontal") * speed));

			float horizontalRotation = Input.GetAxis("Mouse X");
			transform.Rotate(0, horizontalRotation, 0);

			verticalRotation -= Input.GetAxis("Mouse Y");
			camera.transform.localRotation = Quaternion.Euler(verticalRotation, 0, 0);
		}


	}

	public void Reset(){
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
			End();	
		}

		if (collision.gameObject.tag == "Cube"){
			score += 10;
			tmp.text = "Score: " + score.ToString();
			collision.gameObject.SetActive(false);
			cubes.Add(collision.gameObject);
		}
    }

	void ResetCubes(){
		foreach (var cube in cubes)
		{
    		cube.SetActive(true);
		}	
	}
}
