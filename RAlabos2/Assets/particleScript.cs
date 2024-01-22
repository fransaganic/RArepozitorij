using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectScript : MonoBehaviour
{
    [SerializeField] public float TTL = 3f;
    GameObject playerPosition;
    public float time;
    SpriteRenderer sprite;

    // Start is called before the first frame update
    void Start()
    {
        time = 0;
        playerPosition = GameObject.FindGameObjectWithTag("Player");
        sprite = gameObject.GetComponent<SpriteRenderer>();
    }

    // Update is called once per frame
    void Update()
    {
        sprite.color = new Color(sprite.color.r, sprite.color.g, sprite.color.b, TTL / time);
        transform.LookAt(playerPosition.transform);
        time += Time.deltaTime;
        if (time > TTL){
            Destroy(gameObject);
        }
    }
}
