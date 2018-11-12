using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using System;


public class GameManager : MonoBehaviour {
	public List<GameObject> tiles;
	private GameObject tileCube;
	public List<Material> materials;
	public TextMeshPro scoreText;
	public TextMeshPro gameOverText;
	public TextMeshPro bestScoreText;
	public TextMeshPro winText;
	public Material endOfGame;

	private int bestScore = 0;
	private bool win;
	private int score;
	private int[] empty;
	private string[] values = {"2", "4", "8", "16", "32", "64", "128", "256", "512", "1024", "2048"};
	private int choice3;
	private int size;
	private int mergedTile;
	private int bound;
	System.Random rnd;
	
	void Start () {
		Restart();
	}

	public void Restart(){
		win = false;
		size = 0;
		rnd = new System.Random();
		gameOverText.GetComponent<MeshRenderer>().enabled = false;
		winText.GetComponent<MeshRenderer>().enabled = false;
		ScoreUpdate(0);
		empty = new int[16];
				for (int i = 0; i < 16; i++){
			empty[i] = 0;
		}
		for (int i = 0; i < 16; i++){
			tiles[i].GetComponentInChildren<TextMeshPro>().text = "";
		}
		SetNumber(); SetNumber();
		TextUpdate();
	}
	
	void Update () {
		if (Input.GetKeyDown("left"))
        {
            MoveLeft();
        }
        if (Input.GetKeyDown("right"))
        {
            MoveRight();
        }
        if (Input.GetKeyDown("up"))
        {
            MoveUp();
        }
		if (Input.GetKeyDown("down"))
        {
            MoveDown();
        }
		if(CheckGameOver() && !win){
			gameOverText.GetComponent<MeshRenderer>().enabled = true;
			ChangeCubesGrey();
		}
       
	}

	void TextUpdate(){
		ScoreUpdate(score);
		int i = 0;
		for (i = 0; i < 16; i++){
			tileCube = tiles[i].transform.Find("Cube").gameObject;
			if (empty[i] != 0){
				tiles[i].GetComponentInChildren<TextMeshPro>().text = values[empty[i] - 1];
				tileCube.GetComponent<MeshRenderer> ().material = materials[empty[i]-1];

			}
			else{
				tileCube.GetComponent<MeshRenderer> ().material = materials[11];
				tiles[i].GetComponentInChildren<TextMeshPro>().text =  "";
			}			
		}
	}

	void ScoreUpdate(int value){
		score = value;
		scoreText.text = "Score: " + score.ToString();
		if (bestScore < score){
			bestScore = score;
			bestScoreText.text = "Best: " + bestScore.ToString();
		}
	}

	void MoveLeft(){
		for (int i = 0; i < 4; i++){
			bound = 4 * i;
			mergedTile = -1;
			for (int j = 0; j < 3; j++){
				combine(4 * i + j , 4 * i + j + 1);
			}
		}
		SetNumber();
	}

	void MoveRight(){
		for (int i = 0; i < 4; i++){
			bound = 4 * i + 3;
			mergedTile = -1;
			for (int j = 3; j > 0; j--){
				combine(4 * i + j, 4 * i + j - 1);
			}
		}
		SetNumber();		
	}

	void MoveUp(){
		for (int i = 0; i < 4 ; i++){
			bound = i;
			mergedTile = -1;
			for (int j = 1; j < 4; j++){
				combine(i + (j - 1) * 4, i + j * 4);
			}
		}
		SetNumber();		
	}

	void MoveDown(){
		for (int i = 0; i < 4 ; i++){
			bound = 4 * 3 + i; 
			mergedTile = -1;
			for (int j = 3; j > 0; j--){
				combine( i + j * 4, i + (j - 1) * 4);
			}
		}
		SetNumber();		
	}

	bool combine(int field1, int field2){
		if (empty[field1] == empty[field2] && empty[field1] != 0 && mergedTile != field1){
			empty[field1] += 1;
			if(empty[field1] == 11){
				winText.GetComponent<MeshRenderer>().enabled = true;
				win = true;
			}
			mergedTile = field1;
			size--;
			EmptyField(field2);
			TextUpdate();
			int newScore;
			if(int.TryParse(values[empty[field1] - 1], out newScore))
			{
				ScoreUpdate(score + newScore);
			}

			return true;
		}
		if (empty[field1] == 0 && empty[field2] != 0){
			empty[field1] = empty[field2];
			EmptyField(field2);
			if (field1 != bound) {combine(field1 - (field2 - field1), field1);}
			TextUpdate();
			return false;
		}
		else{
			return false;
		}
		
	}

	void EmptyField(int field){
		empty[field] = 0;
	}

	bool CheckEmpty(int i){
		return empty[i] == 0;
	}

	bool SetNumber(){
		if (size >= 16){
			return false;
		}
		size++;
		do{
			choice3 = rnd.Next(0,16);
		}while(!CheckEmpty(choice3));
		empty[choice3] = 1;
		TextUpdate();
		return true;
	}

	bool CheckGameOver(){
		if (size == 16){
			for (int i = 0; i < 4; i++){
				for (int j = 0; j < 3; j++){
					if(empty[4 * i + j] == empty [4 * i + j + 1]){
						return false;
					}
				}
			}
			for (int i = 0; i < 4 ; i++){
				for (int j = 1; j < 4; j++){
					if(empty[i + (j - 1) * 4] == empty[i + j * 4]){
						return false;
					}
				}
			}
			return true;
		}
		return false;
	}

	void ChangeCubesGrey(){
		int i = 0;
		for (i = 0; i < 16; i++){
			tileCube = tiles[i].transform.Find("Cube").gameObject;
			tileCube.GetComponent<MeshRenderer> ().material = endOfGame;		
		}	
	}
}
