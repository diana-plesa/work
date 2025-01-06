using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour
{
    // Start is called before the first frame update

    public float moveSpeed;
    public GameObject ExplosionPrefab;
    private PointManager pointManager;
    void Start()
    {
        pointManager = GameObject.Find("PointManager").gameObject.GetComponent<PointManager>();
        //find the point manager script; kinda like drag and drop, but since bullet is prefab and doesn't exist
        //i have to use this function to find it instead
    }

    // Update is called once per frame
    void Update()
    {
        transform.Translate(Vector2.up * moveSpeed * Time.deltaTime);
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        Vector3 VectorModif = new Vector3(0, (float)1.3, 0);

        if (collision.gameObject.tag == "Enemy")
        {
            Destroy(collision.gameObject);
            pointManager.UpdateScore(50);
            Destroy(gameObject);
            Instantiate(ExplosionPrefab, transform.position + VectorModif, Quaternion.identity);
        }

        if (collision.gameObject.tag == "Boundary")
        {
            Destroy(gameObject);
            
        }
    }
}
