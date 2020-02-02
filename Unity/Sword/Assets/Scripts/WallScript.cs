using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WallScript : MonoBehaviour
{
    public void Collapse(){
        StartCoroutine("DoCollapse");
    }

    IEnumerator DoCollapse(){
        yield return new WaitForSeconds(1);
        while(transform.position.y > -20){
            transform.position = new Vector3(transform.position.x, transform.position.y - (Time.deltaTime * 5), transform.position.z);
            yield return null;
        }
        yield return null;
    }
}
