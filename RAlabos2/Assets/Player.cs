using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{
    [SerializeField] Transform cameraTrans;
    [SerializeField] float movementSpeed = 5f;
    [SerializeField] float mouseSensitivity = 3f;
    Vector2 look;

    // Start is called before the first frame update
    void Start()
    {
        Cursor.lockState = CursorLockMode.Locked;
    }

    // Update is called once per frame
    void Update()
    {
        UpdateLook();
        UpdateMovement();
    }

    void UpdateLook(){
        look.x += Input.GetAxis("Mouse X") * mouseSensitivity;
        look.y += Input.GetAxis("Mouse Y") * mouseSensitivity;

        look.y = Mathf.Clamp(look.y, -89f, 89f);

        cameraTrans.localRotation = Quaternion.Euler(-look.y, 0, 0);
        transform.localRotation = Quaternion.Euler(0, look.x, 0);
    }

    void UpdateMovement(){
        
        var x = Input.GetAxis("Horizontal");
        var y = Input.GetAxis("Vertical");

        var input = new Vector3();

        input += transform.forward * y;
        input += transform.right * x;

        if(Input.GetKey(KeyCode.E)){
             input += transform.up;     
        }

        if(Input.GetKey(KeyCode.Q)){
             input -= transform.up;     
        }

        input = Vector3.ClampMagnitude(input, 1f);

        transform.Translate(input * movementSpeed * Time.deltaTime, Space.World);
    }

  
}
