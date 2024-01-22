using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectPool : MonoBehaviour
{
    public Queue<GameObject> pool;

    public GameObject Origin;
    public GameObject particles;

    [Range(0,1000)]
    [SerializeField]public float SpawnRate = 100;

    [SerializeField] public float rangex1;
    [SerializeField] public float rangex2;
    [SerializeField] public float rangey1;
    [SerializeField] public float rangey2;
    [SerializeField] public float rangez1;
    [SerializeField] public float rangez2;

    // Start is called before the first frame update
    void Start()
    {
        pool = new Queue<GameObject>();
        InvokeRepeating("SpawnObjects", 0, 1 / SpawnRate);
    }

    private void SpawnObjects()
    {
        if(pool.Count > 0){

            GameObject currentObject = pool.Dequeue();

            currentObject.transform.position = Origin.transform.position;
            Vector3 randomForce = new Vector3(Random.Range(rangex1, rangex2), Random.Range(rangey1, rangey2), Random.Range(rangez1, rangez2));
            currentObject.GetComponent<Rigidbody>().AddForce(randomForce);
        }
        else{
            GameObject currentObject = Instantiate(particles, Origin.transform.position, Quaternion.identity);

            currentObject.transform.position = Origin.transform.position;
            Vector3 randomForce = new Vector3(Random.Range(rangex1, rangex2), Random.Range(rangey1, rangey2), Random.Range(rangez1, rangez2));
            currentObject.GetComponent<Rigidbody>().AddForce(randomForce);
        }
    }
}
