////
////  CleaningPage.swift
////  Rug Slug App
////
////  Created by Kaixin Yu on 2/22/23.
////
//
//import SwiftUI
//
//struct CleaningPage: View {
////    Declare variables
//    var battery = true // FIX ME: needs to be replaced to be an input from a file
//    var waste = true // FIX ME: needs to be replaced to be an input from a file
//    var solution = false // FIX ME: needs to be replaced to be an input from a file
//    
//    var body: some View {
//        //        Stacks the items vertically
//        VStack {
//            //            Title of the Page
//            Text("Robot is Cleaning!")
//                .font(.largeTitle)
//                .padding(.bottom, 200)
//            
//            //            THIS IS FOR WASTE TANK:
//            //            FIX ME: ADD INPUT TO THE STATUS
//            HStack {
//                Text("Battery Status: ")
//                    .font(.title2)
//                    .multilineTextAlignment(.leading)
//                    .padding(.leading)
//                Spacer()
//                if (battery == true) {
//                    Text("Needs Charging")
//                        .padding(.trailing)
//                } else {
//                    Text("Charged Enough")
//                        .padding(.trailing)
//                }
//            }
//            .padding(.bottom)
//            
//            //            THIS IS FOR WASTE TANK:
//            //            FIX ME: ADD INPUT TO THE STATUS
//            HStack {
//                Text("Waste Tank Status: ")
//                    .font(.title2)
//                    .multilineTextAlignment(.leading)
//                    .padding(.leading)
//                Spacer()
//                if (waste == true) {
//                    Text("Full")
//                        .padding(.trailing)
//                } else {
//                    Text("Empty")
//                        .padding(.trailing)
//                }
//            }
//            .padding(.bottom)
//            
//            //            THIS IS FOR CHARGING STATION SOLUTION TANK:
//            //            FIX ME: ADD INPUT TO THE STATUS
//            HStack {
//                Text("Solution Tank Status: ")
//                    .font(.title2)
//                    .multilineTextAlignment(.leading)
//                    .padding(.leading)
//                Spacer()
//                if (solution == true) {
//                    Text("Full")
//                        .padding(.trailing)
//                } else {
//                    Text("Empty")
//                        .padding(.trailing)
//                }
//            }
//            .padding(.bottom)
//            
//            
//        }
//        
//        
//    }
//}
//
//struct CleaningPage_Previews: PreviewProvider {
//    static var previews: some View {
//        CleaningPage()
//    }
//}
