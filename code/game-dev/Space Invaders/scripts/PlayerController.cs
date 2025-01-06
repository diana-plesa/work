using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    public float moveSpeed;
    public float xInput;
    

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        xInput = Input.GetAxisRaw("Horizontal"); //getAxisRaw: 0 - no input, -1 - left, 1 - right

        transform.Translate(Vector2.right * moveSpeed *xInput * Time.deltaTime);
        Debug.Log(Screen.width);
        Debug.Log(Screen.height);
    }
}
