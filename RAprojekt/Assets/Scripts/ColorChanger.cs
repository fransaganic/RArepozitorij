using UnityEngine;
using System.Collections;
using System.Diagnostics;
using UnityEngine.UI;




public class ColorChanger : MonoBehaviour {

	private int i = 0;
	public Material red;
	public Material blue;
	public Material green;
	public Material cyan;
	public Material magenta;
	public Material yellow;

	public void changeColor(){
		if(i == 0){
			Red();
			i++;
		}
		else if(i == 1){
			Green();
			i++;
		}
		else if(i == 2){
			Blue();
			i++;
		}
		else if(i == 3){
			Cyan();
			i++;
		}
		else if(i == 4){
			Magenta();
			i++;
		}
		else if(i == 5){
			Yellow();
			i = 0;
		}
			
	}

	public void Red(){
		GameObject.FindGameObjectWithTag("Player").GetComponent<Renderer>().material = red;
	}
	public void Blue(){
		GameObject.FindGameObjectWithTag("Player").GetComponent<Renderer>().material = blue;
	}
	public void Green(){
		GameObject.FindGameObjectWithTag("Player").GetComponent<Renderer>().material = green;
	}
	public void Cyan(){
		GameObject.FindGameObjectWithTag("Player").GetComponent<Renderer>().material = cyan;
	}
	public void Magenta(){
		GameObject.FindGameObjectWithTag("Player").GetComponent<Renderer>().material = magenta;
	}
	public void Yellow(){
		GameObject.FindGameObjectWithTag("Player").GetComponent<Renderer>().material = yellow;
	}

	

}
