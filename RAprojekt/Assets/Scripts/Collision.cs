using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class Collision : MonoBehaviour
{
    [SerializeField] public string material;

    void Update()
    {
        if(GameObject.FindGameObjectWithTag("Player").GetComponent<MeshRenderer>().material.name == material){
            transform.gameObject.GetComponent<BoxCollider>().enabled = false;
        }
        else{
            transform.gameObject.GetComponent<BoxCollider>().enabled = true;
        }
    }
}
