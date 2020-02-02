using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SphereScript : MonoBehaviour
{
    public KnightScript knightScript;
    void OnTriggerStay(Collider other)
    {
		knightScript.InZone(other);
    }

    void OnTriggerExit(Collider other)
    {
        knightScript.OutZone(other);
    }
}
