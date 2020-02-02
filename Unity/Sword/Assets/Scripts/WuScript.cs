using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WuScript : MonoBehaviour
{
    public KnightScript knightScript;

    private void OnTriggerEnter(Collider other)
    {
        if(other.gameObject.CompareTag("Player")){
            knightScript.AddWu(gameObject);        
        }
    }
}
