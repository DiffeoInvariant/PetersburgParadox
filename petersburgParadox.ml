open Core.List
open Core.Container
open Core.Random
open Printf



(*
 *@author: Zane Jakobs
 *@param value: the current amount the player has won
 *@return: result of playing the St. Petersburg Casino game
 *)
let rec run_game v =
  if Random.bool () = false then 2. ** v
  else run_game (v +. 1.)
;;

(*
 *@author: Zane Jakobs
 *@param n: number of samples
 *@return: array where each entry is the value paid to a player
 * in the St. Petersburg Casino game
 *)
let rec game_samples n lst =
match n with
  | 0 -> lst
  | k -> game_samples (k-1) ((run_game 0.)::lst)
 ;;


let sample_mean lst = 
  let sum = List.fold_left ~f:(+.) ~init:(0.) lst in
  sum /. (float_of_int (List.length lst))
;;

let petersburg_paradox trials =
(*  let trialArr = Array.make trials 0. in*)
  let lst = game_samples trials [] in
  sample_mean lst
;;

let numTrials = 100;;

Random.self_init ();;
let m = petersburg_paradox numTrials;;

let () = printf "%f" m ;
  printf "\n";;







