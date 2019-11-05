Pregunta 1)
    SELECT last_name,salary FROM employees
    WHERE salary > 12000
    ORDER BY salary asc;

Pregunta 2)
    SELECT last_name,department_id FROM employees
    WHERE employee_id = 176;

Pregunta 3)
    SELECT last_name, salary FROM employees
    WHERE salary > 12000 OR salary < 5000
    ORDER BY salary desc;

Pregunta 4)
    SELECT last_name, job_id, hire_date FROM employees
    WHERE last_name IN ('Taylor','Matos')
    ORDER BY hire_date asc;

Pregunta 5)
    SELECT last_name, department_id FROM employees
    WHERE department_id IN(20,50)
    ORDER BY first_name asc;

Pregunta 6)
    SELECT last_name as "EMPLOYEE", salary as "MONTHLY_SALARY" FROM employees
    WHERE (salary BETWEEN 5000 AND 12000) 
    AND department_id IN(20,50);

Pregunta 7)
    SELECT last_name, hire_date FROM employees
    WHERE hire_date like '%94';

Pregunta 8)
    SELECT last_name, job_id FROM employees
    WHERE manager_id is NULL;

Pregunta 9)
    SELECT last_name, salary, commission_pct FROM employees
    ORDER BY salary desc, commission_pct desc ;

Pregunta 10)
    SELECT last_name,salary FROM employees
    WHERE salary > &salary_num;

Pregunta 11)
    SELECT employee_id, last_name, salary, department_id FROM employees
    WHERE manager_id = '&manager_num'
    ORDER BY &order_column desc;

Pregunta 12)
    SELECT last_name FROM employees
    WHERE last_name like '__a%';

Pregunta 13)
    SELECT last_name FROM employees
    WHERE last_name like '%a%'  AND last_name like '%e%';

Pregunta 14)
    SELECT last_name, job_id, salary FROM employees
    WHERE (job_id='SA_REP' OR job_id='ST_CLERK') AND salary NOT IN(2500,3500,7000)
    ORDER BY salary desc;

Pregunta 15)
    SELECT last_name AS "Employee", salary AS "Monthly_Salary", commission_pct FROM employees
    WHERE commission_pct= .2
    ORDER BY salary desc;



