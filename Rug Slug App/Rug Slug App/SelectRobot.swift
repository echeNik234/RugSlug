////
////  SelectRobot.swift
////  Rug Slug App
////
////  Created by Kaixin Yu on 2/14/23.
////
//
//import SwiftUI
//
//struct SelectRobot: View {
////    @State private var showConnect = true
//    var body: some View {
//        VStack(alignment: .leading) {
//            
////            Text("")
////                .padding(.top, 30)
//            
////            TITLE OF THE PAGE
////            if showConnect {
////
////                VStack(alignment: .leading) {
////                    Text("Connect to your")
////                        .padding(.leading, 70)
////                    Text("Rug Slug Bot!")
////                        .padding(.leading, 90)
////                }
////                    .font(.largeTitle)
////                    .multilineTextAlignment(.center)
////            }
//            
//            NavigationView{
//                List {
//                    NavigationLink(destination: HomePage(), label: {Text("Let's Connect!")
//                            .navigationBarBackButtonHidden(true)
//                    })
//                    .navigationBarBackButtonHidden(true)
//                        
//                }
//                .navigationBarBackButtonHidden(true)
//                
////                .toolbar {
////                    ToolbarItem(placement: .navigationBarLeading) {
////
////                        VStack {
//////                            Text("")
//////                                .padding(.top, 30)
////                            Text("Connect to your")
////                                .padding(.leading, 70.0)
////                            Text("Rug Slug Bot!").padding(.leading, 90)
////                        }
////                        .font(.largeTitle)
////                        .multilineTextAlignment(.center)
////
////                    }
////                }
////                .navigationTitle(
////                    VStack(alignment: .leading) {
////                        Text("Connect to your")
////                            .padding(.leading, 70)
////                        Text("Rug Slug Bot!")
////                            .padding(.leading, 90)
////                    }
////                )
////                .navigationTitle("Connect!")
//                .navigationBarBackButtonHidden(true) // Deletes the Back Button
//                
//            }
////            .navigationTitle("Welcome to your Rug Slug!")
////            .navigationBarTitleDisplayMode(.inline)
////                }
//            
//        }
////        .padding()
//        
//        //                .fontWeight(.thin)
//        //                .multilineTextAlignment(.center)
//        //                .bold()
//        //                    .font(.largeTitle)//                    .font(Font.custom("Helvetica Neue", size: 36.0))
//        ////                    .padding()
//        //
//        //                HStack {
//        //                    Spacer()
//        //                    List {
//        //                        NavigationLink(destination: HomePage(), label: {Text("Connect Now!")
//        //                                .fontWeight(.bold)
//        //                            .multilineTextAlignment(.center)})
//        //                        .navigationTitle(Text("Connect Now!"))
//        //                    }
//        //                    Spacer()
//        //
//        //                }
//        //            }.padding(20)
//                
//        //        HStack(alignment: .leading) {
//        
//            
//        
//        
//    }
//}
//
//struct SelectRobot_Previews: PreviewProvider {
//    @Binding var showWelcome: Bool
//    static var previews: some View {
//        SelectRobot()
//    }
//}
