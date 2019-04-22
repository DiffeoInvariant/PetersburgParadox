open Core
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
let rec game_samples n =
  if n <= 0 then [| |] else
    let arr = (Array.create n 0.) in
    Array.map ~f:(run_game) arr;
    arr
;;

let fadd a b = 
  a +. b;;

let sample_mean arr =
  let tot = Array.fold_right ~f:fadd arr ~init:0. in
  tot /. (Float.of_int (Array.length arr))
;;

let petersburg_paradox trials =
(*  let trialArr = Array.make trials 0. in*)
  let arr = game_samples trials in
  let mu = sample_mean arr in
  mu
;;

let numTrials = 100;;

Random.self_init ();;
let m = petersburg_paradox numTrials;;

let () = printf "%f" m ;
  printf "\n";;







