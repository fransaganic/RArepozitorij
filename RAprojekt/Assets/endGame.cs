using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class endGame : MonoBehaviour
{
    void Update(){
        if(transform.position.y <= -400){
            SceneManager.LoadScene(0);
        }
    }
}
