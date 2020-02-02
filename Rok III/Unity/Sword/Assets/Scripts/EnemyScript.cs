using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;
using UnityEngine.UI;

public class EnemyScript : MonoBehaviour
{

    public GameObject player;
    public bool dead;
    public int level = 1;
    public bool boss;
    public Slider slider;
        
    float fullHealth;
    float currentHealth;
    bool hitting;
    bool attack;
    Animator animator;
    CharacterController controller;
    Vector3 currentTarget;
    NavMeshAgent enemy;
    Vector3 position0;
    Camera mainCamera;
    int exp;

    void Start()
    {
        //slider.gameObject.SetActive(false);
        mainCamera = Camera.main;
        exp = level * 70;
        enemy = GetComponent<NavMeshAgent>();
        controller = GetComponent<CharacterController> ();
        animator = GetComponent<Animator> ();
        fullHealth = 100 * level;
        currentHealth = fullHealth;
        position0 = transform.position;
        currentTarget = position0;
        SliderManager();
    }

    void Update()
    {
        if(attack && !dead){
            currentTarget = player.transform.position;
        }
        if(dead){
            currentTarget = transform.position;
        }
        
        enemy.destination = currentTarget;
        if (!dead){
            MoveTowardsTarget();
        }

        slider.transform.LookAt(mainCamera.transform);
    }

	bool TargetReached() {
  		float distanceToTarget = Vector3.Distance(transform.position, currentTarget);
  		return (distanceToTarget < 2f);
	}

    private void SliderManager(){
        slider.value = (float)currentHealth / fullHealth;
    }

    public void Hit(float damage){
        currentHealth -= damage;
        SliderManager();
        if (currentHealth <= 0){
            Death();
        }
        else{
            Damage();
            StartCoroutine("DamageTime");
        }
    }

    public int GetExp(){
        return exp;
    }

    void MoveTowardsTarget() {
        if(TargetReached() && !hitting && attack) {
            gameObject.GetComponent<NavMeshAgent>().isStopped = true;
            hitting = true;
            animator.SetInteger("condition", 3);
            StartCoroutine("HitpointsTime");
            StartCoroutine("FullAttackTime1");
        }
        if (!hitting){
            if (TargetReached()){
                animator.SetInteger("condition", 0);
            }
            else{
                animator.SetInteger("condition", 2);
            }
        }

    }

    private IEnumerator HitpointsTime(){
        yield return new WaitForSeconds(0.3F);
        if (animator.GetInteger("condition") == 3){
            AttackEnemiesInRange();
        }
    }

    void AttackEnemiesInRange(){
        foreach(Collider col in Physics.OverlapSphere((transform.position + transform.forward * 0.5f), 1.0f)){
            if(col.gameObject.CompareTag("Player")){
                KnightScript ec = col.transform.GetComponent<KnightScript>();
                if(ec == null) continue;
                else {
                    int a = Random.Range(70, 100);
                    ec.Hit(a);
                }
                return;
            }
        }
    }    

    private IEnumerator FullAttackTime1() {
		yield return new WaitForSeconds(0.6f);
        hitting = false;
        gameObject.GetComponent<NavMeshAgent>().isStopped = false;
        Idle();
        
	}

    void Death(){
        
       animator.SetInteger("condition", -1);
        dead = true;
        attack = false;
    }

    void Damage(){
        animator.SetInteger("condition", 1);
    }

    void Idle(){
        if(!dead){ 
            animator.SetInteger("condition", 0);
        }
        else{
            animator.SetInteger("condition", -1);
        }
    }
    

    private IEnumerator DamageTime(){
        yield return new WaitForSeconds(0.3f);
        Idle();
    }

    public void StartAttack(){
        if (!attack){
            attack = true;
            currentTarget = player.transform.position;
        }
    }
    
    public void StopAttack()
    {
        attack = false;
        currentTarget = position0;
    }
}
