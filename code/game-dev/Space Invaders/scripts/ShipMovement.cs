using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShipMovement : MonoBehaviour
{
    
    public float moveSpeed;
    public GameObject shipExplosion;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        transform.Translate(Vector2.right * moveSpeed * Time.deltaTime);
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.tag == "Boundary") 
        {
            transform.Translate(Vector2.down * 20 * Time.deltaTime);
            moveSpeed = moveSpeed * -1;
        }

        if (collision.gameObject.tag == "Hero")
        {
            Destroy(collision.gameObject);
            Instantiate(shipExplosion, transform.position, Quaternion.identity);
        }
    }
}
