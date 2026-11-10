# Projeto_Atividade_02_Caixa_Eletronico_em_C

Simulador de caixa eletrônico feito em **C**, que roda no terminal. O programa recebe um valor de saque, calcula quais notas entregar, atualiza o saldo e salva um recibo em arquivo.

## O que o programa faz

- Começa com **saldo de R$ 1000**.
- Pede o valor do saque e confere se ele é válido.
- Escolhe quais notas entregar, respeitando as notas que ainda existem no caixa.
- Mostra as notas entregues e o novo saldo.
- Salva um **recibo** no arquivo `recibo.txt` e mostra o recibo na tela.
- Mostra quantas notas ainda restam no caixa.
- Pergunta se você quer fazer outro saque.

## Notas disponíveis no caixa

| Nota | Quantidade inicial |
|------|--------------------|
| R$ 100 | 0 |
| R$ 50 | 4 |
| R$ 20 | 10 |
| R$ 10 | 5 |
| R$ 5 | 10 |

O caixa começa com R$ 500 em notas, menos que o saldo de R$ 1000. Por isso, um saque pode ser negado por falta de notas mesmo que a conta tenha saldo.

## Regras do saque

O saque só é feito se:

1. O valor for **maior que zero**.
2. O valor for **múltiplo de 5** (o caixa só tem notas de 100, 50, 20, 10 e 5).
3. O valor não for **maior que o saldo**.
4. O caixa tiver **notas suficientes** para formar o valor.

Se alguma regra falhar, o programa avisa o motivo e **nenhum recibo é gerado**.

Se o usuário digitar letras em vez de números, o programa avisa ("Digite apenas numeros") e pede de novo.

## Quando o programa termina

- Quando você responde `0` na pergunta "Deseja realizar outro saque?".
- Quando o saldo chega a zero.
- Quando o caixa fica sem notas.

## Como compilar e executar

É preciso ter um compilador C instalado, como o **GCC**.

```bash
gcc Atividade_Caixa_Eletronico_C.c -o caixa
./caixa
```

No Windows, o executável gerado é `caixa.exe`. Para rodar no terminal, use `caixa`.

## Exemplo de uso

Saque de 130:

```
Saldo atual: 1000
Digite valor do saque: 130

Notas entregues:
Notas de 50: 2
Notas de 20: 1
Notas de 10: 1
Novo saldo: 870
Recibo 1 salvo no arquivo recibo.txt

------ RECIBO 1 ------
Valor do saque: 130
Notas de 50: 2
Notas de 20: 1
Notas de 10: 1
Saldo anterior: 1000
Saldo atual: 870
----------------------

Notas que ainda tem no caixa:
Notas de 100: 0
Notas de 50: 2
Notas de 20: 9
Notas de 10: 4
Notas de 5: 10

Deseja realizar outro saque? (1 - Sim / 0 - Nao):
```

## Sobre o recibo

- Os recibos ficam salvos em `recibo.txt`, na mesma pasta do programa.
- Cada saque novo é **adicionado no final** do arquivo, sem apagar os anteriores.
- Ao iniciar, o programa conta quantos recibos já existem para a numeração continuar de onde parou.

## Conceitos de C usados

- Variáveis, vetores (`notas`, `qtd`, `usadas`) e laços (`while`, `for`)
- Condições (`if` / `else`)
- Leitura de dados com `scanf` e validação de entrada
- Manipulação de arquivos (`fopen`, `fprintf`, `fgets`, `fclose`)
- Funções de texto (`strstr`, `sprintf`)

## Estrutura do projeto

```
Projeto_atividade_02-Caixa_Eletronico_em_C/
├── Atividade_Caixa_Eletronico_C.c   # código-fonte
├── README.md                        # este arquivo
└── recibo.txt                       # criado automaticamente após o primeiro saque
```
