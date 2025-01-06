using System.Collections;
using System.Collections.Generic;
using System.Security.Cryptography.X509Certificates;
using Unity.Mathematics;
using UnityEngine;
using UnityEngine.UI;

public class PlayerLives : MonoBehaviour
{
    public int lives = 3;
    public GameObject playerExplosion;
    public Image[] livesUI;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.collider.gameObject.tag == "Enemy") //looks at collider, not parent object (Ships)
        {
            Destroy(collision.collider.gameObject);
            Instantiate(playerExplosion, transform.position, quaternion.identity);

            lives -= 1;
            for (int i = 0; i < livesUI.Length; i++)
            {
                if (i < lives)
                {
                    livesUI[i].enabled = true;
                }
                else
                {
                    livesUI[i].enabled = false;
                }
            }

            if (lives <= 0)
            {
                Destroy(gameObject);
                //Instantiate(playerExplosion, transform.position, quaternion.identity);
            }
        }
    }
}
