﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraScr : MonoBehaviour {

	public GameObject player;
    private Vector3 offset;
	void Start () {
		offset = transform.position - player.transform.position;
	}
}