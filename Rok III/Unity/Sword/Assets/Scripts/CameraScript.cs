using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraScript : MonoBehaviour
{
	public Transform lookAt;
    private Vector3 offset;

    private float distance = 3.0f;
    private float currentX = 0.0f;
    private float currentY = 30.0f;
    private float sensivityX = 4.0f;
    private float sensivityY = 2.0f;

    private const float Y_MAX = 70.0f;
    private const float Y_MIN = -5.0f;

    private const float DISTANCE_MAX = 10.0f;
    private const float DISTANCE_MIN = 1.0f; 

    
	void Update () {
        currentX += Input.GetAxis("Mouse X") * sensivityX;
        currentY -= Input.GetAxis("Mouse Y") * sensivityY;
        distance += Input.GetAxis("Mouse ScrollWheel");
        distance = Mathf.Clamp(distance, DISTANCE_MIN, DISTANCE_MAX);
        currentY = Mathf.Clamp(currentY, Y_MIN, Y_MAX);
	}
	
	
	void LateUpdate () {
		Vector3 dir = new Vector3(0, 0, -distance);
        Quaternion rotation = Quaternion.Euler(currentY, currentX, 0);
        transform.position = lookAt.position + rotation * dir;
        transform.LookAt(lookAt.position);
	}
}
