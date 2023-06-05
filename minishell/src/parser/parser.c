
//Cuantos separadores hay
// << < >> > |
// hola "que tal '" ''' como estas  -> 1
// hola que tal "|" como estas -> 1
// hola que tal '"|"' como estas -> 1
// hola que tal << como estas -> 3
// <<<<< -> 3
// << << < -> 3

/**
 * @brief utils de how many tokens I need
 * 
 * @param c 
 * @return int 
 */

int chr_can_be_separator(char c)
{
  if (c == '<' || c == '|' || c == '>')
    return 1;
  return (0);
}



//Quitar todos los espacios irrelevantes
//hola    que tal "'      "      "' "     
//hola que tal "'      " "' "
char *clean_irrelveant_spaces_in_input(char *input)
{

  char *new_input;
  int quote; // ? comillas dobles
  int miniquote;// ? comillas simples

  quote = 0;
   miniquote = 0;
  new_input = ft_strdup("");
  while(*input)
  {
    //Evaluar los quotes
    if (*input == '"' && quote == 0 && miniquote != 1 )
      quote = 1;
    else if (*input == '"' && quote == 1)
      quote = 0;
    if (*input == '\'' && miniquote == 0 && quote != 1)
      miniquote = 1;
    else if (*input == '\'' && miniquote == 1)
      miniquote = 0;

    new_input = strjoin_char(new_input, *input)
  }
  

}
//Quitar todos los espacios irrelevantes
//     hola    que tal "'      "      "' "     
//hola que tal "'      " "' "

// ! Nuevo entry point

int sanitize_input(char *input)
{
    input = ft_trim(input, " ");
    input = clean_irrelveant_spaces_in_input(input);

}

/**
 * @brief function para usar despues de sanitaze_input
 * 
 * @param input 
 * @return int 
 */


int how_many_tokens_i_need(char *input)
{
  int quote; // ? comillas dobles
  int miniquote;// ? comillas simples
  int tokens; // ? numero de tokens

  quote = 0;
  miniquote = 0;
  tokens = 0;
  while (*input)
  {
    //Evaluar los quotes
    if (*input == '"' && quote == 0 && miniquote != 1 )
      quote = 1;
    else if (*input == '"' && quote == 1)
      quote = 0;
    if (*input == '\'' && miniquote == 0 && quote != 1)
      miniquote = 1;
    else if (*input == '\'' && miniquote == 1)
      miniquote = 0;

    //....  
    if (chr_can_be_separator(*input))
    {
      if (*input == '<' && *(input + 1) == '<')
      {
        tokens++;
        input++;
      }
      else if (*input == '>' && *(input + 1) == '>')
      {
        tokens++;
        input++;
      }else
      {
        tokens++;
      }
      if (*(input + 1) + 1)
    }
  }

  return (tokens);
}

//Tenemos que ir controlando si quote o miniquote abierto
/*int how_many_argc_have_the_token(char *input)
{

}
*/