using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FadeScript : MonoBehaviour
{
    public float time1 = 2f;
    public float time2 = 5f;
    public float wait = 2;

    void Start(){
        if (gameObject.tag == "Skills"){
            time1 = 1f;
            time2 = 1f;
            wait = 0f;
        }
    }
    public void Fade(){
        StartCoroutine("DoFade");
    }

    IEnumerator DoFade(){
        yield return new WaitForSeconds(wait);
        CanvasGroup canvasGroup = GetComponent<CanvasGroup>();
        while(canvasGroup.alpha > 0){
            canvasGroup.alpha -= Time.deltaTime / time1;
            yield return null;
        }
        canvasGroup.interactable = false;
        yield return null;
    }

    public void Show(){
        StartCoroutine("DoShow");
    }

    IEnumerator DoShow(){
        yield return new WaitForSeconds(wait);
        CanvasGroup canvasGroup = GetComponent<CanvasGroup>();
        while(canvasGroup.alpha < 1){
            canvasGroup.alpha += Time.deltaTime / time2;
            yield return null;
        }
        canvasGroup.interactable = false;
        yield return null;
    }
}
