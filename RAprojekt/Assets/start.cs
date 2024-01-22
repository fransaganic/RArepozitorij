using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class start : MonoBehaviour
{
    public void Start(){
        SceneManager.LoadScene(1);
    }
    public void Exit(){
        Application.Quit();
    }
}
