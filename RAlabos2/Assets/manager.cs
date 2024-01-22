using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class manager : MonoBehaviour
{
    public GameObject canvas;
    // Start is called before the first frame update
    void Start()
    {
        canvas.SetActive(false);
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.I) && canvas.activeSelf == false){
            Debug.Log("Hello");
            canvas.SetActive(true);
            Time.timeScale = 0;
        }
        if (Input.GetKeyDown(KeyCode.I) && canvas.activeSelf == true){
            canvas.SetActive(false);
            Time.timeScale = 1;
        }
    }
}
