#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#pragma once

using namespace std;

class Curve {
public:

	struct Segment {
		vector<glm::vec3> tocke;
		vector<glm::vec3> tockeTangente;
	};

	vector<glm::vec3> points;
	vector<glm::vec3> tockeAproksimativneKrivulje;
	vector<glm::vec3> tockeInterpolacijskeKrivulje;
	int points_count;
	vector<int> factors;  //malloc
	int divs;

	GLuint VAO;
	GLuint VBO[3];
	GLuint EBO;


	//novo

	vector<Segment> segmenti;
	

	void ucitajBuffere() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(4, VBO);

		glBindVertexArray(0);
	}

	void dodajTocku(glm::vec3 tocka) {
		points.push_back(tocka);
		points_count = points.size();
		divs = 20 * points_count;

		if (points_count > 1) {
			draw_Bezier();
		}

		if (points_count > 3) {

			draw_Interpolacijska();
		}

	}

	void dodajTocku2(glm::vec3 tocka) {
		points.push_back(tocka);
		points_count = points.size();
		divs = 10 * points_count;
		


		if (points_count > 3) {
			draw_Krivulja(points_count - 3, divs);
		}

	}

	void compute_factors(int n) {
		int a = 1;

		for (int i = 0; i < points_count; i++) {
			factors.push_back(0);
		}

		for (int i = 1; i <= n + 1; i++) {

			factors[i - 1] = a;

			a = a * (n - i + 1) / i;

		}
	}

	void draw_Bezier() {

		int n = points_count - 1;
		vector<glm::vec3> izracunateTocke;

		compute_factors(n);

		float t, b;


		for (int i = 0; i <= divs; i++) {
			t = 1.0f / divs * i;
			glm::vec3 point = glm::vec3(0.0, 0.0, 0.0);
			for (int j = 0; j <= n; j++) {
				if (j == 0) {
					b = factors[j] * pow(1 - t, n);
				}
				else if (j == n) {
					b = factors[j] * pow(t, n);
				}
				else {
					b = factors[j] * pow(t, j) * pow(1 - t, n - j);
				}

				point.x += b * points[j].x;
				point.y += b * points[j].y;
				point.z += b * points[j].z;

			}

			izracunateTocke.push_back(point);

		}

		tockeAproksimativneKrivulje = izracunateTocke;

	}


	void draw_Krivulja(int indeks, int divs) {
		//novo


		//cout << indeks << endl;
		glm::mat4 B = glm::mat4(glm::vec4(-1, 3, -3, 1),
			glm::vec4(3, -6, 0, 4),
			glm::vec4(-3, 3, 3, 1),
			glm::vec4(1, 0, 0, 0));

		glm::mat4x3 Btangenta = glm::mat4x3(glm::vec3(-1, 2, -1),
			glm::vec3(3, -4, 0),
			glm::vec3(-3, 2, 1),
			glm::vec3(1, 0, 0));

		Segment noviSegmenti;

		for (int i = 0; i <= divs; i++) {
			float t = (i * 1.0f) / divs;
			glm::vec4 T = glm::vec4(t * t * t, t * t, t, 1);
			glm::mat3x4 R = glm::mat3x4(glm::vec4(points[indeks - 1].x, points[indeks].x, points[indeks + 1].x, points[indeks + 2].x),
										glm::vec4(points[indeks - 1].y, points[indeks].y, points[indeks + 1].y, points[indeks + 2].y),
										glm::vec4(points[indeks - 1].z, points[indeks].z, points[indeks + 1].z, points[indeks + 2].z));
			glm::vec3 novaTocka = T * (1.0f / 6.0f) * B * R;
			//cout << "Nova tocka dodana" << endl;
			noviSegmenti.tocke.push_back(novaTocka);
			noviSegmenti.tockeTangente.push_back(novaTocka);

			glm::vec3 Ttangenta = glm::vec3(t * t, t, 1);
			glm::vec3 VektorTangente = (1.0f / 6.0f) * Ttangenta * Btangenta * R;
			noviSegmenti.tockeTangente.push_back(VektorTangente + novaTocka);
		}

		//cout << "KREPAO?" << endl;
		segmenti.push_back(noviSegmenti);
	}

	void draw_Interpolacijska() {

		

		//staro
		/*
		vector<glm::vec3> izracunateTocke;

		glm::mat4 T(1.0f);
		T[0] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		T[1] = glm::vec4(1.0f / 27.0f, 1.0f / 9.0f, 1.0f / 3.0f, 1.0f);
		T[2] = glm::vec4(8.0f / 27.0f, 4.0f / 9.0f, 2.0f / 3.0f, 1.0f);
		T[3] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

		glm::mat4 Tinverz = glm::inverse(T);


		glm::mat4 P;

		for (int i = 0; i < 4; i++) {

			P[i] = glm::vec4(float(points[points.size() - 1 - i].x), float(points[points.size() - 1 - i].y), float(points[points.size() - 1 - i].z), 0.0f);

		}

		glm::mat4 K = P * Tinverz; //suprotan redoslijed

		for (int i = 0; i <= divs; i++) {

			float t = 1.0f / divs * i;

			glm::vec3 tocka = glm::vec3(0.0, 0.0, 0.0);

			tocka.x = pow(t, 3) * K[0].x + pow(t, 2) * K[1].x + t * K[2].x + K[3].x;
			tocka.y = pow(t, 3) * K[0].y + pow(t, 2) * K[1].y + t * K[2].y + K[3].y;
			tocka.z = pow(t, 3) * K[0].z + pow(t, 2) * K[1].z + t * K[2].z + K[3].z;

			izracunateTocke.push_back(tocka);

		}

	

		tockeInterpolacijskeKrivulje = izracunateTocke;
		*/

	}

	void iscrtajKrivulje(Shader& sjencar) {
		glUseProgram(sjencar.ID);

		glLineWidth(4);


		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

		glBufferData(GL_ARRAY_BUFFER, points.size() * 3 * sizeof(float), &points[0], GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
		glEnableVertexAttribArray(0);

		sjencar.setUniformVec4("ourColor", glm::vec4(0.0, 0.0, 0.0, 0.0));

		glDrawArrays(GL_LINE_STRIP, 0, points.size());
		// novo
		
		

		
		for (int i = 0; i < segmenti.size(); i++) {
			
			sjencar.setUniformVec4("ourColor", glm::vec4(0.0, 0.0, 1.0, 0.0));
			glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
			glEnableVertexAttribArray(0);
			//cout << "Pukooooo" << endl;
			glBufferData(GL_ARRAY_BUFFER, segmenti.at(i).tocke.size() * 3 * sizeof(float), &segmenti.at(i).tocke[0], GL_DYNAMIC_DRAW);
			glDrawArrays(GL_LINE_STRIP, 0, segmenti.at(i).tocke.size());

			
			sjencar.setUniformVec4("ourColor", glm::vec4(0.0, 1.0, 0.0, 0.0));
			glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
			glEnableVertexAttribArray(0);
			glBufferData(GL_ARRAY_BUFFER, segmenti.at(i).tockeTangente.size() * 3 * sizeof(float), &segmenti.at(i).tockeTangente[0], GL_DYNAMIC_DRAW);
			glDrawArrays(GL_LINE_STRIP, 0, segmenti.at(i).tockeTangente.size());
		}
		

		/*
		if (points_count > 1) {

			glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);

			glBufferData(GL_ARRAY_BUFFER, tockeAproksimativneKrivulje.size() * 3 * sizeof(float), &tockeAproksimativneKrivulje[0], GL_DYNAMIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
			glEnableVertexAttribArray(0);

			sjencar.setUniformVec4("ourColor", glm::vec4(1.0, 0.0, 1.0, 0.0));
			glDrawArrays(GL_LINE_STRIP, 0, tockeAproksimativneKrivulje.size());


		}
		*/
		/*
		if (points_count > 3) {

			glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);

			glBufferData(GL_ARRAY_BUFFER, tockeInterpolacijskeKrivulje.size() * 3 * sizeof(float), &tockeInterpolacijskeKrivulje[0], GL_DYNAMIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
			glEnableVertexAttribArray(0);

			sjencar.setUniformVec4("ourColor", glm::vec4(0.0, 1.0, 1.0, 0.0));
			glDrawArrays(GL_LINE_STRIP, 0, tockeInterpolacijskeKrivulje.size());
		}
		*/

		glLineWidth(1);

		glBindVertexArray(0);
	}


};