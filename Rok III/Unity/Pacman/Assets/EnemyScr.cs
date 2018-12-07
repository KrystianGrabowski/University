using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class EnemyScr : MonoBehaviour {
	
	public GameObject player;
	public PlayerScr playerScr;
	private NavMeshAgent enemy;
	private Vector3 currentTarget;
	public Vector3 startPosition;

	public int size;
	public Vector3[] patrolPoints;
	private bool hunting;

	void Start () {
		enemy = GetComponent<NavMeshAgent>();
		GetNewPosition();
		enemy.speed = 5;
		hunting = false;
	}

	void GetNewPosition(){
		int number = Random.Range(0, size);
		currentTarget = patrolPoints[number];
		enemy.destination = currentTarget;
	}
	
	void Update () {
		if (playerScr.gameOver){
			 enemy.isStopped = true;
		}
		else if (!hunting && TargetReached()){
			GetNewPosition();
		}
	}

	public void Reset(){
		transform.position = startPosition;
		enemy.isStopped = false;
	}

	bool TargetReached() {
  		float distanceToTarget = Vector3.Distance(transform.position, currentTarget);
  		return (distanceToTarget < 2f);
	}

	void OnTriggerStay(Collider other)
    {
		if (other.gameObject.tag == "Player"){
			currentTarget = player.transform.position;
			hunting = true;
			enemy.destination = currentTarget;
			enemy.speed = 12;

		}	
    }
	
	void OnTriggerExit(Collider other)
    {
		if (other.gameObject.tag == "Player"){
			hunting = false;
			GetNewPosition();
			enemy.speed = 5;

		}
    }
}
