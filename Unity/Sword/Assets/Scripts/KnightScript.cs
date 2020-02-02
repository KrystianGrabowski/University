using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class KnightScript : MonoBehaviour
{
	public AudioClip gameSound;
	public AudioClip skill1Sound;
	public AudioClip skill2Sound;
    public AudioClip wallSound;
    public AudioClip enemySound;
	AudioSource source;
    public WallScript ws;
    public GameObject deathEffect;
    public GameObject explosionEffect;
    public GameObject magic1;
    public GameObject magic2;
    public GameObject toFade;
    public GameObject toShow;
    public GameObject endScreen;
    public GameObject skills;
    public Text skill2Number;
    public Transform expBar;
    public Text levelText;
    public Text wuText;
    public Transform hpBar;
    public Text hpText;


    float regularSpeed = 4;
    float rotation = 0f;
    float rotationSpeed = 100;
    float gravity = 8;
    float doubleSpeed;
    float currentSpeed;
    int level = 1;
    Vector3 move = new Vector3(0,0,0);
    CharacterController controller;
    Animator animator;
    float fullHealth = 1000;
    float currentHealth;
    int experience;
    int neededExperience;
    int currentLevelExperience;
    int wu;
    int bosses = 3;
    bool dead = false;
    bool skillLock = false;
    int skill2 = 3;

    void Start()
    {
        source = GetComponent<AudioSource>();
        source.PlayOneShot(gameSound);
        experience = 0;
        currentLevelExperience = 0;
        neededExperience = 100;
        currentHealth = fullHealth;
        controller = GetComponent<CharacterController> ();
        animator = GetComponent<Animator> ();
        doubleSpeed = regularSpeed * 2;
        currentSpeed = regularSpeed;
        expBar.GetComponent<Image>().fillAmount = experience/neededExperience;
    }

    void Update()
    {
        if(!dead){
            Movement();
            Attack();
            if (!skillLock){
                MagicSkills();
            }
        }
        if (Input.GetKey (KeyCode.Escape)){
            StartCoroutine("Menu");
        }

    }

    void Movement(){

        if (controller.isGrounded){
            if (animator.GetBool("attacking")){
                    return;
            }
            MoveForward();
            MoveBackward();
            MoveFaster();
        }
        MoveForwardStop();
        MoveBackwardStop();
        MoveFasterStop();
        rotation += Input.GetAxis ("Horizontal") * rotationSpeed * Time.deltaTime;
        transform.eulerAngles = new Vector3 (0, rotation, 0);

        move.y -= gravity * Time.deltaTime;
        controller.Move (move * Time.deltaTime);        
    }

    public void AddWu(GameObject go){
        go.SetActive(false);
        wu += 1;
        if (wu >= 11){
            source.PlayOneShot(wallSound);
            var expl = Instantiate(explosionEffect, new Vector3(88, 10, 755), transform.rotation);
            ws.Collapse();
            Destroy(expl,5);
        }
        wuText.text = wu + "/11";
    }

    void MoveForward(){
        if (Input.GetKey (KeyCode.W)){
            animator.SetBool("forward", true);
            animator.SetBool("running", true);
            animator.SetInteger ("movement", 2);
            move = new Vector3 (0, 0, 1) * currentSpeed;
            move = transform.TransformDirection (move);
        }
    }

    void MoveForwardStop(){
        if (Input.GetKeyUp (KeyCode.W)){
            animator.SetBool("forward", false);
            animator.SetBool("running", false);
            animator.SetInteger ("movement", 0);
            move = new Vector3 (0, 0, 0);
        }
    }

    void MoveBackward(){
        if (Input.GetKey (KeyCode.S)){
            animator.SetBool("running", true);
            animator.SetInteger ("movement", -1);
            move = new Vector3 (0, 0, -1) * currentSpeed;
            move = transform.TransformDirection (move);
        }
    }

    void MoveBackwardStop(){
        if (Input.GetKeyUp (KeyCode.S)){
            animator.SetBool("running", false);
            animator.SetInteger ("movement", 0);
            move = new Vector3 (0, 0, 0);
        }
    }

    void MoveFaster(){
        if (animator.GetBool("forward")){
            if(Input.GetKey (KeyCode.LeftShift)){
                currentSpeed = doubleSpeed;
                animator.SetInteger ("movement", 3);
            }
        }
    }
    void MoveFasterStop(){
        if (animator.GetBool("forward")){
            if(Input.GetKeyUp (KeyCode.LeftShift)){
                    currentSpeed = regularSpeed;
                    animator.SetInteger ("movement", 2);
                }
        }
    }

    void Attack(){
        if (!animator.GetBool("attacking")){
            if (controller.isGrounded){
                if (Input.GetMouseButtonDown(0)){
                    if (animator.GetBool("running")){
                        animator.SetBool("running", false);
                        move = new Vector3 (0, 0, 0);
                    }
                    animator.SetBool("attacking", true);
                    animator.SetInteger("movement", 1);
                    StartCoroutine("DamageTime");
                    StartCoroutine("FullAttackTime");
                }
            }
        }
    }

    private IEnumerator FullAttackTime() {
		yield return new WaitForSeconds(0.5f);
        animator.SetBool("attacking", false);
        animator.SetInteger("movement", 0);
	}

    private IEnumerator DamageTime(){
        yield return new WaitForSeconds(0.25F);
        if (animator.GetInteger("movement") == 1){
            AttackEnemiesInRange();
        }
    }

    void LevelUp(){
        level += 1;
        levelText.text = "Level " + level;
        currentLevelExperience += neededExperience;
        neededExperience += neededExperience;
        expBar.GetComponent<Image>().fillAmount = (float)(experience - currentLevelExperience) / neededExperience;
    }

    void AttackEnemiesInRange(){
        foreach(Collider col in Physics.OverlapSphere((transform.position + transform.forward * 0.5f), 1.0f)){
            if(col.gameObject.CompareTag("Enemy")){
                EnemyScript ec = col.transform.GetComponent<EnemyScript>();
                if(ec == null) continue;
                else {
                    int a = level * Random.Range(20, 50);
                    ec.Hit(a);
                }
            }
        }
    }
    public void InZone(Collider other)
    {
		if (other.gameObject.tag == "Enemy"){
            EnemyScript ec = other.gameObject.transform.GetComponent<EnemyScript>();
            if (ec.dead){
                experience += ec.GetExp();
                source.PlayOneShot(enemySound);
                expBar.GetComponent<Image>().fillAmount = (float)(experience - currentLevelExperience) / neededExperience;
                ec.tag = "EnemyDead";
                StartCoroutine(DestroyObject(other.gameObject));
                if (experience - currentLevelExperience >= neededExperience ){
                    LevelUp();
                }
                if (ec.boss){
                    bosses--;
                    if (bosses == 0){
                        End();
                    }
                }
            }
            else{
                ec.StartAttack();
            }
		}
    }

    private IEnumerator DestroyObject(GameObject obj){
        yield return new WaitForSeconds(5);
        Destroy(obj);
    }

    public void OutZone(Collider other)
    {
		if (other.gameObject.tag == "Enemy"){
            EnemyScript ec = other.gameObject.transform.GetComponent<EnemyScript>();
            ec.StopAttack();
		}
    }

    void GameOver(){
        FadeScript fs0  = skills.GetComponent<FadeScript>();
        fs0.Fade();
        FadeScript fs1  = toFade.GetComponent<FadeScript>();
        fs1.Fade();
        FadeScript fs2  = toShow.GetComponent<FadeScript>();
        fs2.Show();
        dead = true;
        StartCoroutine("Menu");
    }

    public void Hit(float damage){
        if (currentHealth - damage >= 0){
            currentHealth -= damage;
        }
        else{
            currentHealth = 0;
        }

        hpBar.GetComponent<Image>().fillAmount = (float)currentHealth / fullHealth;
        hpText.text = "HP " + currentHealth + "/" + fullHealth;

        if (currentHealth <= 0){
            var expl = Instantiate(deathEffect, transform.position, transform.rotation);
            GameOver();
        }
    }
    void MagicSkills(){
        if (Input.GetKey (KeyCode.Alpha1)){
            MagicSkill1();
        }
        if (Input.GetKey (KeyCode.Alpha2)){
            MagicSkill2();
        }
    }

    public void HideCursor(){
        Cursor.visible = false;
    }



    void MagicSkill1(){
        source.PlayOneShot(skill1Sound);
        var expl = Instantiate(magic1, transform.position, transform.rotation);
        Destroy(expl,2);
        foreach(Collider col in Physics.OverlapSphere((transform.position), 10.1f)){
            if(col.gameObject.CompareTag("Enemy")){
                EnemyScript ec = col.transform.GetComponent<EnemyScript>();
                if(ec == null) continue;
                else {
                    int a = level * 30;
                    ec.Hit(a);
                }
            }
        }
        StartCoroutine("SkillTime");
    }

    void MagicSkill2(){
        skill2--;
        if (skill2 >= 0){
            source.PlayOneShot(skill2Sound);
            var expl = Instantiate(magic2, transform.position + new Vector3(0,1,0), transform.rotation);
            Destroy(expl,5);
            currentHealth = fullHealth;
            hpBar.GetComponent<Image>().fillAmount = (float)currentHealth / fullHealth;
            hpText.text = "HP " + currentHealth + "/" + fullHealth;
            skill2Number.text = skill2 + "";
            StartCoroutine("SkillTime");
        }
    }

    private IEnumerator SkillTime(){
        FadeScript fs0  = skills.GetComponent<FadeScript>();
        fs0.Fade();
        skillLock = true;
        yield return new WaitForSeconds(15);
        skillLock = false;
        fs0.Show();
    }

    private IEnumerator Menu(){
        yield return new WaitForSeconds(8);
        Cursor.visible = true;
        SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }

    void End(){
        FadeScript fs0  = skills.GetComponent<FadeScript>();
        fs0.Fade();
        FadeScript fs1  = toFade.GetComponent<FadeScript>();
        fs1.Fade();
        FadeScript fs2  = endScreen.GetComponent<FadeScript>();
        fs2.Show();
        dead = true;
        StartCoroutine("Menu");
    }
}
