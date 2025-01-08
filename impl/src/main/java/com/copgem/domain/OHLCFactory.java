package com.copgem.domain;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.UncheckedIOException;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Pattern;
import java.util.logging.Level;
import java.util.logging.Logger;

public class OHLCFactory {
        private static Logger log = Logger.getLogger(OHLCFactory.class.getName());
       public static List<OHLC> fromInvestingCSV(InputStream inputStream) { // https://www.investing.com
      
        List<OHLC> olhcvList = new ArrayList<>();
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream))) {
            String line;
            reader.readLine(); // Skip the header
            while ((line = reader.readLine()) != null) {
                // Split the line by the '|' delimiter
                String[] fields = line.split("\\|");
                if(fields.length < 6) {
                    log.log(Level.WARNING, "Invalid line: {}", line);
                    continue;
                }
                // Parse the fields
                LocalDateTime date = LocalDate.parse(fields[0]).atStartOfDay();
                double close = Double.parseDouble(fields[1]);
                double open = Double.parseDouble(fields[2]);
                double high = Double.parseDouble(fields[3]);
                double low = Double.parseDouble(fields[4]);
                double volume = Double.parseDouble(fields[5]);
            
                // Create an OLHCV object and add it to a list or process it as needed
                OHLC olhcv = new OHLC(date, open, high, low, close, volume);
                // Add olhcv to a list or process it
                olhcvList.add(olhcv);
            }
        } catch (IOException cause) {
          throw new UncheckedIOException(cause);
        }
        return olhcvList;
    }

    public static Pair<List<OHLC>, List<OHLC>> fromForexSB(InputStream frameStream, InputStream pointStream) {
        try (
            BufferedReader frameOLHCVReader = new BufferedReader(new InputStreamReader(frameStream));
            BufferedReader pointOLHCVReader = new BufferedReader(new InputStreamReader(pointStream));
        ) {
            return new Pair<List<OHLC>, List<OHLC>>(
                fromForexSB(frameStream), 
                fromForexSB(pointStream)
            ) ;
        }catch (IOException cause) {
            throw new UncheckedIOException(cause);
        }

        
    }

    public static List<OHLC> fromForexSB(InputStream inputStream) {
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
        Pattern pattern = Pattern.compile("\\s+");
        List<OHLC> olhcvList = new ArrayList<>();
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream))) {
            String line;
            reader.readLine(); // Skip the header
            while ((line = reader.readLine()) != null) {
                // Split the line by the '|' delimiter
                String[] fields = pattern.split(line);
                String dateString = fields[0] + " " + fields[1];
                // Parse the fields
                LocalDateTime date = LocalDateTime.parse(dateString, formatter); // Open	High Low	Close	Volume
                double open = Double.parseDouble(fields[2]);
                double high = Double.parseDouble(fields[3]);
                double low = Double.parseDouble(fields[4]);
                double close = Double.parseDouble(fields[5]);
                double volume = Double.parseDouble(fields[6]);
            
                // Create an OLHCV object and add it to a list or process it as needed
                OHLC olhcv = new OHLC(date, open, high, low, close, volume);
                // Add olhcv to a list or process it
                olhcvList.add(olhcv);
            }
        } catch (IOException cause) {
          throw new UncheckedIOException(cause);
        }

        return olhcvList;
    }

    public static List<OHLC> fromPepperStone(InputStream inputStream) {
           return fromForexSB(inputStream);
    }
}
